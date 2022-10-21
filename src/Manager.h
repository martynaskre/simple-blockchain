//
// Created by Martynas Skrebė on 2022-10-13.
//

#ifndef SIMPLE_BLOCKCHAIN_MANAGER_H
#define SIMPLE_BLOCKCHAIN_MANAGER_H


#include "Pools/UsersPool.h"
#include "Pools/TransactionsPool.h"
#include "Block.h"
#include "Pools/BlocksPool.h"
#include <map>

class Manager {
    UsersPool users;
    TransactionsPool transactions;
    BlocksPool blocks;

    void performMining();
    Block selectCandidate(std::vector<Block> candidates);
    void displayUserStatistics();
public:
    void bootstrap();
};


#endif //SIMPLE_BLOCKCHAIN_MANAGER_H
