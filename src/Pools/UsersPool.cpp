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
        std::string name = "user";

        name.append(std::to_string(i));

        User user = User(name, stringGenerator.setLength(100).generate(), numberGenerator.setLength(100, 1000000).generate());

        users.insert(std::make_pair(user.getPublicKey(), user));
    }
}
