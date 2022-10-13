//
// Created by Martynas Skrebė on 2022-10-13.
//

#ifndef BLOCKCHAIN_USERSPOOL_H
#define BLOCKCHAIN_USERSPOOL_H


#include <unordered_map>
#include "User.h"

class UsersPool {
    std::unordered_map<std::string, User> users;

public:
    void generateUsers();
};


#endif //BLOCKCHAIN_USERSPOOL_H
