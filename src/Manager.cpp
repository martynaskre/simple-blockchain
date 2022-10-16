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
        return users.getRandomUser();
    });

    Logger::setState(true);

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

        transactions.erase(range.first, range.second);
    }

    std::cout << "done" << std::endl;
}

void Manager::initializeBlocks() {
    Block genesis = Block("sw", 0, "1", 1, {});
    genesis.mine();

    blocks.insert(std::pair(1, genesis));
}
