//
// Created by Martynas Skrebė on 2022-10-19.
//

#ifndef BLOCKCHAIN_BLOCKSPOOL_H
#define BLOCKCHAIN_BLOCKSPOOL_H


#include "Block.h"
#include <map>

class BlocksPool {
    std::map<int, Block> blocks;

public:
    BlocksPool();
    std::pair<int, Block*> addBlock(Block block);
    std::optional<Block*> getBlock(int sequence);
    std::string getLatestHash();
};


#endif //BLOCKCHAIN_BLOCKSPOOL_H
