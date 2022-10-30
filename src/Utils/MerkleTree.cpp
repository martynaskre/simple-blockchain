//
// Created by Martynas Skrebė on 2022-10-30.
//

#include "MerkleTree.h"
#include <utility>
#include "Hash.h"

Node::Node(std::string hash): hash(std::move(hash)), parent(nullptr), left(nullptr), right(nullptr) {}

MerkleTree::MerkleTree(): root(nullptr) {}

MerkleTree::MerkleTree(const std::vector<std::string>& values): root(nullptr) {
    for (auto &value: values) {
        addLeaf(value);
    }

    generateMerkleTree();
}

void MerkleTree::addLeaf(const std::string& val) {
    leafs[val] = new Node(hash(val));
}

void MerkleTree::generateMerkleTree() {
    std::vector<Node*> tree;

    for (auto &el: this->leafs) {
        tree.push_back(el.second);
    }

    this->root = buildMerkelTree(tree);
}

Node *MerkleTree::buildMerkelTree(std::vector<Node*>& tree) {
    if (tree.empty()) {
        return nullptr;
    }

    if (tree.size() == 1) {
        return tree.at(0);
    }

    if (tree.size() % 2 != 0) {
        tree.push_back(tree.back());
    }

    std::vector<Node*> merkleLeaf;

    for (auto it = tree.begin(); it != tree.end(); it += 2) {
        auto leftNode = **it;
        auto rightNode = **(it + 1);

        Node* node = new Node(hash(leftNode.hash + rightNode.hash));

        node->left = &leftNode;
        node->right = &rightNode;

        leftNode.parent = node;
        rightNode.parent = node;

        merkleLeaf.push_back(node);
    }

//    std::vector<Node*> topLine;
//
//    std::string concatedHashes;
//    std::string newHash;
//    Node *tNode;
//    for (auto it = line.begin(); it != line.end(); it += 2)
//    {
//        concatedHashes = (**it).hash + (**(it + 1)).hash;
//        newHash = hash(concatedHashes);
//        tNode = new Node(newHash);
//
//        tNode->left = *it;
//        tNode->right = *(it + 1);
//
//        (**it).parent = tNode;
//        (**(it + 1)).parent = tNode;
//
//        topLine.push_back(tNode);
//    }

    return this->buildMerkelTree(merkleLeaf);
}

Node MerkleTree::getRoot() {
    return *root;
}
