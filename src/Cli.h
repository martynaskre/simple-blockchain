//
// Created by Martynas Skrebė on 2022-10-18.
//

#ifndef BLOCKCHAIN_CLI_H
#define BLOCKCHAIN_CLI_H


#include "Pools/UsersPool.h"
#include "Pools/BlocksPool.h"

class Cli {
    UsersPool users;
    BlocksPool blocks;
    static const std::vector<std::pair<std::string, std::string>> commands;

    void printHelp();
public:
    void run(int argc, char *argv[]);
};


#endif //BLOCKCHAIN_CLI_H
