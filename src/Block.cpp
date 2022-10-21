//
// Created by Martynas Skrebė on 2022-10-15.
//

#include "Block.h"
#include <utility>
#include "Hash.h"
#include <sstream>
#include <iostream>
#include "Utils/Application.h"
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

void Block::setHash(std::string hash) {
    if (isMined) {
        throw std::invalid_argument("Block is already mined");
    }

    identifier = std::move(hash);
    isMined = true;
}

void Block::setNonce(int newNonce) {
    if (isMined) {
        throw std::invalid_argument("Block is already mined");
    }

    nonce = newNonce;
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

std::string Block::getMerkleHash() {
    return merkleHash;
}

int Block::getNonce() const {
    return nonce;
}

int Block::getDifficultyTarget() const {
    return difficultyTarget;
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
    if (!Application::runningInDebug()) {
        std::ofstream writer("blocks/" + std::to_string(sequence) + ".dat");

        writer << to_json();

        writer.close();
    }
}

Block::Block(std::string identifier, std::string previousHash, std::time_t timestamp, std::string version,
             std::string merkleHash, int nonce, int difficultyTarget): identifier(std::move(identifier)),
             previousHash(std::move(previousHash)), timestamp(timestamp), version(std::move(version)), merkleHash(std::move(merkleHash)), nonce(nonce), difficultyTarget(difficultyTarget) {}

std::string Block::to_json() {
    return nlohmann::json{
        {"hash", getHash()},
        {"previous_hash", getPreviousHash()},
        {"timestamp", getTimestamp()},
        {"version", getVersion()},
        {"merkle_hash", getMerkleHash()},
        {"nonce", getNonce()},
        {"difficulty_target", getDifficultyTarget()},
    }.dump();
}

Block Block::from_json(nlohmann::json &json) {
    return {
        json["hash"].get<std::string>(),
        json["previous_hash"].get<std::string>(),
        json["timestamp"].get<std::time_t>(),
        json["version"].get<std::string>(),
        json["merkle_hash"].get<std::string>(),
        json["nonce"].get<int>(),
        json["difficulty_target"].get<int>(),
    };
}
