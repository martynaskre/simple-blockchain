//
// Created by Martynas Skrebė on 2022-10-13.
//

#include <iostream>
#include <utility>
#include "UsersPool.h"
#include "Utils/StringGenerator.h"
#include "Utils/NumberGenerator.h"
#include <fstream>
#include <Manager.h>

UsersPool::UsersPool() {
    if (!Manager::runningInDebug()) {
        for (const auto & entry : std::filesystem::directory_iterator("users")) {
            auto user = User::fromFile(entry.path());

            users.insert(std::make_pair(user.getPublicKey(), user));
        }
    }
}

void UsersPool::createUser(std::string name, std::string passphrase, unsigned int balance) {
    User user = User(std::move(name), std::move(passphrase), balance);

    users.insert(std::make_pair(user.getPublicKey(), user));
}

void UsersPool::generateUsers() {
    StringGenerator stringGenerator = {};
    NumberGenerator numberGenerator = {};

    int toGenerate = 1000;

    for (int i = 1; i <= toGenerate; i++) {
        std::string name = "User";

        name.append(std::to_string(i));

        createUser(name, stringGenerator.setLength(100).generate(), numberGenerator.setLength(100, 1000000).generate());
    }
}

std::optional<User*> UsersPool::getUser(const std::string& publicKey) {
    try {
        return &users.at(publicKey);
    } catch (const std::out_of_range& e) {
        //
    }

    return std::nullopt;
}

User* UsersPool::getRandomUser() {
    NumberGenerator numberGenerator = {};

    return &std::next(std::begin(users), numberGenerator.setLength(0, users.size()).generate())->second;
}

std::pair<UsersPool::usersMap::iterator, UsersPool::usersMap::iterator> UsersPool::getUsers() {
    return {
        users.begin(),
        users.end()
    };
}
