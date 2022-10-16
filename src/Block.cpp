//
// Created by Martynas Skrebė on 2022-10-15.
//

#include "Block.h"
#include <utility>
#include "Hash.h"
#include <sstream>
#include <iostream>

Block::Block(std::string previousHash, std::time_t timestamp, std::string version, int difficulty,
             const transactions& transactions) {
    this->previousHash = std::move(previousHash);
    this->timestamp = timestamp;
    this->version = std::move(version);
    this->merkleHash = makeMerkleHash(transactions);
    this->nonce = 0;
    this->difficultyTarget = difficulty;

    this->identifier = makeIdentifier(nonce);
}

std::string Block::getHash() {
    return identifier;
}

std::string Block::getPreviousHash() {
    return previousHash;
}

std::time_t Block::getTimestamp() const {
    return timestamp;
}

std::string Block::getVersion() {
    return version;
}

int Block::getNonce() const {
    return nonce;
}

int Block::getDifficultyTarget() const {
    return difficultyTarget;
}

void Block::mine() {
    bool mined = false;

    std::string guessedHash = makeIdentifier(nonce);
    std::string difficulty = std::string(difficultyTarget, '0');

    while (!mined) {
        if (guessedHash.rfind(difficulty, 0) == 0) {
            mined = true;

            identifier = guessedHash;
        } else {
            nonce++;

            guessedHash = makeIdentifier(nonce);
        }
    }
}

std::string Block::makeIdentifier(int newNonce) {
    std::stringstream hashBuilder;

    hashBuilder << previousHash << timestamp << merkleHash << newNonce;

    return hash(hashBuilder.str());
}

std::string Block::makeMerkleHash(const std::unordered_set<std::string>& transactions) {
    std::stringstream transactionsString;

    for (auto transaction: transactions) {
        transactionsString << transaction;
    }

    return hash(transactionsString.str());
}
