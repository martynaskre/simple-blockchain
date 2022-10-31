//
// Created by Martynas Skrebė on 2022-10-18.
//

#include "Cli.h"
#include <vector>
#include <string>
#include <iostream>
#include "Utils/Color.h"
#include <iomanip>

const std::vector<std::pair<std::string, std::string>> Cli::commands = {
        {"--help", "Shows available commands"},
        {"--wallet {public_key}", "Returns information about wallet"},
        {"--block {sequence}", "Returns information about block"}
};

void Cli::run(int argc, char **argv) {
    if (argc <= 1) {
        std::cout << Color::RED << "No arguments were specified." << Color::RESET << std::endl << std::endl;

        this->printHelp();

        return;
    }

    std::vector<std::string> args(argv + 1, argv + argc);

    if ((args[0] == "--help" || args[0] == "--h" || args[0] == "-h" || args[0] == "--help") && argc == 2) {
        this->printHelp();

        return;
    }

    if (args[0] == "--wallet" && argc == 3) {
        std::string walletKey = args[1];

        auto user = users.getUser(walletKey);

        if (user.has_value()) {
            std::cout << Color::CYAN << "Name: " << Color::RESET << user.value()->getName() << std::endl;
            std::cout << Color::CYAN << "Balance: " << Color::RESET << user.value()->getBalance() << std::endl;
        } else {
            std::cout << Color::RED << "Wallet does not exist." << Color::RESET << std::endl;
        }

        return;
    }

    if (args[0] == "--block" && argc == 3) {
        int blockKey = stoi(args[1]);

        auto block = blocks.getBlock(blockKey);

        if (block.has_value()) {
            std::time_t t = block.value()->getTimestamp();
            auto tm = *std::localtime(&t);

            std::cout << Color::CYAN << "Hash: " << Color::RESET << block.value()->getHash() << std::endl;
            std::cout << Color::CYAN << "Previous hash: " << Color::RESET << block.value()->getPreviousHash() << std::endl;
            std::cout << Color::CYAN << "Timestamp: " << Color::RESET << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S.%z%Z") << std::endl;
            std::cout << Color::CYAN << "Version: " << Color::RESET << block.value()->getVersion() << std::endl;
            std::cout << Color::CYAN << "Merkle hash: " << Color::RESET << block.value()->getMerkleHash() << std::endl;
            std::cout << Color::CYAN << "Nonce: " << Color::RESET << block.value()->getNonce() << std::endl;
            std::cout << Color::CYAN << "Difficulty target: " << Color::RESET << block.value()->getDifficultyTarget() << std::endl;
        } else {
            std::cout << Color::RED << "Block does not exist." << Color::RESET << std::endl;
        }

        return;
    }

    std::cout << Color::RED << "Invalid arguments were specified." << Color::RESET << std::endl << std::endl;
    this->printHelp();
}

void Cli::printHelp() {
    std::cout << Color::YELLOW << "Available commands:" << Color::RESET << std::endl;

    for (const auto& command: commands) {
        std::cout << std::setfill(' ') << std::setw(4) << "";
        std::cout << std::setw(40) << std::left << Color::GREEN + command.first + Color::RESET;
        std::cout << command.second << std::endl;
    }
}
