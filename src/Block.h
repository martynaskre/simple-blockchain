//
// Created by Martynas Skrebė on 2022-10-15.
//

#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H


#include <string>
#include <unordered_set>
#include <nlohmann/json.hpp>

class Block {
    std::string identifier;
    std::string previousHash;
    std::time_t timestamp;
    std::string version;
    std::string merkleHash;
    int nonce;
    int difficultyTarget;
    bool isMined = false;

    std::string makeMerkleHash(const std::unordered_set<std::string>& transactions);

    Block(std::string identifier, std::string previousHash, std::time_t timestamp, std::string version, std::string merkleHash, int nonce, int difficultyTarget);
public:
    typedef std::unordered_set<std::string> transactions;

    Block(std::string previousHash, std::time_t timestamp, std::string version, int difficulty, const transactions& transactions);

    void setHash(std::string hash);
    void setNonce(int newNonce);

    std::string getHash();
    std::string getPreviousHash();
    std::time_t getTimestamp() const;
    std::string getVersion();
    std::string getMerkleHash();
    int getNonce() const;
    int getDifficultyTarget() const;

    std::string makeIdentifier(int newNonce);

    void save(int sequence);

    std::string to_json();
    static Block from_json(nlohmann::json& json);
};


#endif //BLOCKCHAIN_BLOCK_H
