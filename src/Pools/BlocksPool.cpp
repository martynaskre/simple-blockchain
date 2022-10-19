//
// Created by Martynas Skrebė on 2022-10-19.
//

#include "BlocksPool.h"
#include <filesystem>
#include <fstream>
#include <iostream>

BlocksPool::BlocksPool() {
    for (const auto &entry: std::filesystem::directory_iterator("blocks")) {
        std::ifstream read(entry.path());
        nlohmann::json data = nlohmann::json::parse(read);

        std::string sequence = entry.path();
        sequence.erase(sequence.begin(), sequence.begin() + 7);
        sequence.erase(sequence.end() - 4, sequence.end());

        auto block = Block::from_json(data);

        blocks.insert(std::make_pair(stoi(sequence), block));
    }
}

std::pair<int, Block*> BlocksPool::addBlock(Block block) {
    int sequence = blocks.rbegin()->first + 1;
    block.save(sequence);

    auto it = blocks.insert(std::pair(sequence, block));

    return {
        it.first->first,
        &it.first->second
    };
}

std::optional<Block*> BlocksPool::getBlock(int sequence) {
    try {
        return &blocks.at(sequence);
    } catch (const std::out_of_range& e) {
        //
    }

    return std::nullopt;
}

std::string BlocksPool::getLatestHash() {
    return blocks.rbegin()->second.getHash();
}
