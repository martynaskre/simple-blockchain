//
// Created by Martynas Skrebė on 2022-10-13.
//

#include "Manager.h"
#include <iostream>
#include "Utils/Logger.h"
#include "Block.h"
#include <filesystem>

bool Manager::isDebug = false;

void Manager::bootstrap() {

    Logger::setState(false);

    initializeBlocks();

    if (runningInDebug()) {
        users.generateUsers();
    }

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

        int sequence = blocks.rbegin()->first + 1;

        block.save(sequence);
        auto iterator = blocks.insert(std::pair(sequence, block));

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
    for (const auto &entry: std::filesystem::directory_iterator("blocks")) {
        auto block = Block::fromFile(entry.path());

        int sequence = (blocks.empty()) ? 1 : blocks.rbegin()->first + 1;

        blocks.insert(std::make_pair(sequence, block));
    }
}

void Manager::displayUserStatistics() {
    auto bounds = users.getUsers();
    unsigned int min = bounds.first->second.getBalance(), max = 0, total = 0;
    UsersPool::usersMap::iterator minIt, maxIt;

    for (auto i = bounds.first; i != bounds.second; i++) {
        User user = i->second;

        total += user.getBalance();

        if (user.getBalance() > max) {
            max = user.getBalance();
            maxIt = i;
        } else if (user.getBalance() < min) {
            min = user.getBalance();
            minIt = i;
        }
    }

    if (max > total) {
        std::cout << "xujne" << std::endl;
    }

    Logger::info("Total coins in circulation: " + std::to_string(total));
    Logger::info(maxIt->second.getPublicKey() + " Richest user: " + std::to_string(max));
    Logger::info(minIt->second.getPublicKey() + " Poorest user: " + std::to_string(min));
}

bool Manager::runningInDebug() {
    return isDebug;
}
