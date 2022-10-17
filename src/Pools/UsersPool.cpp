//
// Created by Martynas Skrebė on 2022-10-13.
//

#include <iostream>
#include "UsersPool.h"
#include "Utils/StringGenerator.h"
#include "Utils/NumberGenerator.h"

void UsersPool::generateUsers() {
    StringGenerator stringGenerator = {};
    NumberGenerator numberGenerator = {};

    int toGenerate = 1000;

    for (int i = 1; i <= toGenerate; i++) {
        std::string name = "User";

        name.append(std::to_string(i));

        User user = User(name, stringGenerator.setLength(100).generate(), numberGenerator.setLength(100, 1000000).generate());

        users.insert(std::make_pair(user.getPublicKey(), user));
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
