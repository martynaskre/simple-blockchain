//
// Created by Martynas Skrebė on 2022-10-13.
//

#ifndef SIMPLE_BLOCKCHAIN_MANAGER_H
#define SIMPLE_BLOCKCHAIN_MANAGER_H


#include "Pools/UsersPool.h"
#include "Pools/TransactionsPool.h"
#include "Block.h"
#include <map>

class Manager {
    static bool isDebug;
    UsersPool users;
    TransactionsPool transactions;
    std::map<int, Block> blocks;

    void initializeBlocks();
    void displayUserStatistics();
public:
    void bootstrap();

    static bool runningInDebug();
};


#endif //SIMPLE_BLOCKCHAIN_MANAGER_H
