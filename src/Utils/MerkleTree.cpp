//
// Created by Martynas Skrebė on 2022-10-30.
//

#include "MerkleTree.h"
#include <utility>
#include "Hash.h"

MerkleTree::MerkleTree(const std::vector<std::string>& values) {
    leafs = values;

    generateMerkleTree();
}

void MerkleTree::addLeaf(const std::string& val) {
    leafs.push_back(val);
}

void MerkleTree::generateMerkleTree() {
    bc::hash_list tree;

    for (auto &leaf: this->leafs) {
        tree.push_back(stringToHashDigest(leaf));
    }

    this->root = buildMerkelTree(tree);
}

bc::hash_digest MerkleTree::buildMerkelTree(libbitcoin::hash_list &merkle) {
    if (merkle.empty()) {
        return bc::null_hash;
    } else if (merkle.size() == 1) {
        return merkle[0];
    }

    while (merkle.size() > 1) {
        if (merkle.size() % 2 != 0) {
            merkle.push_back(merkle.back());
        }

        assert(merkle.size() % 2 == 0);

        bc::hash_list newMerkle;

        for (auto it = merkle.begin(); it != merkle.end(); it += 2) {
            bc::data_chunk concat_data(bc::hash_size * 2);

            auto concat = bc::serializer<decltype(concat_data.begin())>(concat_data.begin());

            concat.write_hash(*it);
            concat.write_hash(*(it + 1));

            bc::hash_digest newRoot = stringToHashDigest(hash(bc::encode_base16(concat_data)));

            newMerkle.push_back(newRoot);
        }

        merkle = newMerkle;
    }

    return merkle[0];
}

std::string MerkleTree::getRoot() {
    return bc::encode_hash(root);
}

bc::hash_digest MerkleTree::stringToHashDigest(const std::string& val) {
    bc::hash_digest newRoot;

    if (!bc::decode_hash(newRoot, val)) {
        throw std::invalid_argument("Invalid hash provided");
    }

    return newRoot;
}
