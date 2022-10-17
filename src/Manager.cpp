//
// Created by Martynas Skrebė on 2022-10-13.
//

#include "Manager.h"
#include <iostream>
#include "Utils/Logger.h"
#include "Block.h"

void Manager::bootstrap() {
    Logger::setState(false);

    initializeBlocks();

    users.generateUsers();
    transactions.generateTransactions([this]() -> User {
        return *users.getRandomUser();
    });

    Logger::setState(true);

    displayUserStatistics();

    while (!transactions.isEmpty()) {
        auto range = transactions.getRange(0, (transactions.size() > 100) ? 100 : transactions.size());

        Block::transactions trans;

        for (auto i = range.first; i != range.second; i++) {
            auto transaction = i->second;

            trans.insert(transaction.getId());
        }

        Block block = Block(blocks.rbegin()->second.getHash(), std::time(nullptr), "1", 1, trans);

        block.mine();

        auto iterator = blocks.insert(std::pair(blocks.rbegin()->first + 1, block));

        Logger::info("Block " + std::to_string(iterator.first->first) + " was mined");

        for (auto i = range.first; i != range.second; i++) {
            Transaction transaction = i->second;

            auto sender = users.getUser(transaction.getSender());
            auto receiver = users.getUser(transaction.getReceiver());

            if (sender.has_value() && receiver.has_value()) {
                auto amount = transaction.getAmount();

                sender.value()->setBalance(sender.value()->getBalance() - amount);
                receiver.value()->setBalance(receiver.value()->getBalance() + amount);

                Logger::info("Sending from: " + sender.value()->getPublicKey() + ", to: " + receiver.value()->getPublicKey() + ", amount: " + std::to_string(amount));
            }
        }

        transactions.erase(range.first, range.second);
    }

    displayUserStatistics();
}

void Manager::initializeBlocks() {
    Block genesis = Block("sw", 0, "1", 1, {});
    genesis.mine();

    blocks.insert(std::pair(1, genesis));
}

void Manager::displayUserStatistics() {
    auto bounds = users.getUsers();
    unsigned int min = 0, max = 0, total = 0;
    UsersPool::usersMap::iterator minIt, maxIt;

    for (auto i = bounds.first; i != bounds.second; i++) {
        User user = i->second;

        total += user.getBalance();

        if (user.getBalance() > max) {
            max = user.getBalance();
            maxIt = i;
        } else if (user.getBalance() < min || min == 0) {
            min = user.getBalance();
            minIt = i;
        }
    }

    Logger::info("Total coins in circulation: " + std::to_string(total));
    Logger::info(maxIt->second.getPublicKey() + " Richest user: " + std::to_string(max));
    Logger::info(minIt->second.getPublicKey() + " Poorest user: " + std::to_string(min));
}
