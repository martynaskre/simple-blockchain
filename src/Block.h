//
// Created by Martynas Skrebė on 2022-10-15.
//

#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H


#include "string"
#include "unordered_set"

class Block {
    std::string identifier;
    std::string previousHash;
    std::time_t timestamp;
    std::string version;
    std::string merkleHash;
    int nonce;
    int difficultyTarget;

    std::string makeIdentifier(int newNonce);
    std::string makeMerkleHash(const std::unordered_set<std::string>& transactions);
public:
    typedef std::unordered_set<std::string> transactions;

    Block(std::string previousHash, std::time_t timestamp, std::string version, int difficulty, const transactions& transactions);

    std::string getHash();
    std::string getPreviousHash();
    std::time_t getTimestamp() const;
    std::string getVersion();
    int getNonce() const;
    int getDifficultyTarget() const;

    void mine();
};


#endif //BLOCKCHAIN_BLOCK_H
