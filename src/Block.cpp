//
// Created by Martynas Skrebė on 2022-10-15.
//

#include "Block.h"
#include <utility>
#include "Hash.h"
#include <sstream>
#include <iostream>
#include "Manager.h"
#include <fstream>

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

void Block::save(int sequence) {
    if (!Manager::runningInDebug()) {
        std::ofstream writer("blocks/" + std::to_string(sequence) + ".dat");

        writer << getHash() << std::endl
            << getPreviousHash() << std::endl
            << getTimestamp() << std::endl
            << getVersion() << std::endl
            << getNonce() << std::endl
            << getDifficultyTarget();

        writer.close();
    }
}

Block Block::fromFile(const std::string& filename) {
    std::ifstream read(filename);

    std::string identifier, previousHash, version, merkleHash;
    std::time_t timestamp;
    int nonce, difficultyTarget;

    read >> identifier >> previousHash >> timestamp >> version >> nonce >> difficultyTarget;

    return {identifier, previousHash, timestamp, version, merkleHash, nonce, difficultyTarget};
}

Block::Block(std::string identifier, std::string previousHash, std::time_t timestamp, std::string version,
             std::string merkleHash, int nonce, int difficultyTarget): identifier(std::move(identifier)),
             previousHash(std::move(previousHash)), timestamp(timestamp), version(std::move(version)), merkleHash(std::move(merkleHash)), nonce(nonce), difficultyTarget(difficultyTarget) {}
