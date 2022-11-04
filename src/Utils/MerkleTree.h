//
// Created by Martynas Skrebė on 2022-10-30.
//

#ifndef BLOCKCHAIN_MERKLETREE_H
#define BLOCKCHAIN_MERKLETREE_H


#include <string>
#include <map>
#include <vector>
#include "bitcoin/bitcoin.hpp"

class MerkleTree {
    bc::hash_digest root{};
    std::vector<std::string> leafs;

    bc::hash_digest buildMerkelTree(bc::hash_list& merkle);
    bc::hash_digest stringToHashDigest(const std::string& val);
public:
    MerkleTree() = default;
    explicit MerkleTree(const std::vector<std::string>& values);

    void addLeaf(const std::string& val);
    void generateMerkleTree();

    std::string getRoot();
};


#endif //BLOCKCHAIN_MERKLETREE_H
