//
// Created by Martynas Skrebė on 2022-10-13.
//

#include "Manager.h"
#include <iostream>
#include "Utils/Logger.h"
#include "Block.h"
#include "Utils/NumberGenerator.h"
#include <omp.h>

void Manager::bootstrap() {
    users.generateUsers();

    transactions.generateTransactions([this]() -> User {
        return *users.getRandomUser();
    });

    displayUserStatistics();
    performMining();
    displayUserStatistics();
}

void Manager::performMining() {
    NumberGenerator numberGenerator{};

    while (!transactions.isEmpty()) {
        std::vector<Block> candidates;

        for (int i = 0; i < 5; i++) {
            int maxTransactions = numberGenerator.setLength(0, 500).generate();

            auto range = transactions.getRange(0, (transactions.size() > maxTransactions) ? maxTransactions : transactions.size());

            Block::transactions trans;

            for (auto x = range.first; x != range.second; x++) {
                auto transaction = x->second;

                trans.push_back(transaction);
            }

            candidates.emplace_back(blocks.getLatestHash(), std::time(nullptr), "1", 5, trans);
        }

        auto block = selectCandidate(candidates);

        auto newBlock = blocks.addBlock(block);

        Logger::info("Block " + std::to_string(newBlock.first) + " was mined");

        for (auto transaction: block.getTransactions()) {
            auto sender = users.getUser(transaction.getSender());
            auto receiver = users.getUser(transaction.getReceiver());

            if (sender.has_value() && receiver.has_value()) {
                auto amount = transaction.getAmount();

                sender.value()->setBalance(sender.value()->getBalance() - amount);
                receiver.value()->setBalance(receiver.value()->getBalance() + amount);

                Logger::info("Sending from: " + sender.value()->getPublicKey() + ", to: " + receiver.value()->getPublicKey() + ", amount: " + std::to_string(amount));
            }

            transactions.erase(transaction.getId());
        }
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

    Logger::info("Total coins in circulation: " + std::to_string(total));
    Logger::info(maxIt->second.getPublicKey() + " Richest user: " + std::to_string(max));
    Logger::info(minIt->second.getPublicKey() + " Poorest user: " + std::to_string(min));
}

Block Manager::selectCandidate(std::vector<Block> candidates) {
    Block* selected;

    #pragma omp parallel num_threads(candidates.size()), shared(candidates, selected), default(none)
    {
        #pragma omp for
        for (auto &block: candidates) {
            int index = &block - &candidates[0];

            bool mined = false;
            int newNonce = block.getNonce();

            std::string guessedHash = block.makeIdentifier(newNonce);
            std::string difficulty = std::string(block.getDifficultyTarget(), '0');

            while (!mined) {
                if (guessedHash.rfind(difficulty, 0) == 0) {
                    mined = true;

                    block.setNonce(newNonce);
                    block.setHash(guessedHash);

                    #pragma omp cancellation point for

                    #pragma omp critical
                    {
                        Logger::info("Block candidate " + std::to_string(index + 1) + " was selected");

                        selected = &block;
                    };

                    #pragma omp cancel for
                } else {
                    newNonce++;

                    guessedHash = block.makeIdentifier(newNonce);
                }
            }
        }
    }

    return *selected;
}
