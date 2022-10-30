//
// Created by Martynas Skrebė on 2022-10-30.
//

#ifndef BLOCKCHAIN_MERKLETREE_H
#define BLOCKCHAIN_MERKLETREE_H


#include <string>
#include <map>
#include <vector>

struct Node {
    std::string hash;
    Node* parent;
    Node* left;
    Node* right;

    explicit Node(std::string hash);
};

class MerkleTree {
    Node *root;
    std::map<std::string, Node*> leafs;

    Node* buildMerkelTree(std::vector<Node*>& tree);
public:
    MerkleTree();
    explicit MerkleTree(const std::vector<std::string>& values);

    void addLeaf(const std::string& val);
    void generateMerkleTree();

    Node getRoot();
};


#endif //BLOCKCHAIN_MERKLETREE_H
