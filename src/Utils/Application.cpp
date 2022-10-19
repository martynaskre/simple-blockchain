//
// Created by Martynas Skrebė on 2022-10-19.
//

#include "Application.h"
#include <iostream>
#include "Color.h"
#include <vector>
#include <string>

const std::vector<std::pair<std::string, std::string>> Application::commands = {
        {"--help", "Shows available commands"},
        {"--debug {true|false}", "Toggles debug mode. Defaults to true"},
        {"--flush", "Removes generated files"}
};

bool Application::debug = true;

void Application::run(int argc, char **argv) {
    if (argc > 1) {
        std::vector<std::string> args(argv + 1, argv + argc);

        if ((args[0] == "--help" || args[0] == "--h" || args[0] == "-h" || args[0] == "--help") && argc == 2) {
            this->printHelp();

            return;
        }

        if (args[0] == "--debug" && argc == 3 && (args[1] == "true" || args[1] == "false")) {
            bool isDebug = args[1] == "true";

            Application::setDebug(isDebug);
        }

        if (args[0] == "--flush") {
            flushFiles();

            return;
        }
    }

    Manager manager;

    manager.bootstrap();
}

void Application::printHelp() {
    std::cout << Color::YELLOW << "Available commands:" << Color::RESET << std::endl;

    for (const auto& command: commands) {
        std::cout << std::setfill(' ') << std::setw(4) << "";
        std::cout << std::setw(40) << std::left << Color::GREEN + command.first + Color::RESET;
        std::cout << command.second << std::endl;
    }
}

void Application::setDebug(bool isDebug) {
    debug = isDebug;
}

bool Application::runningInDebug() {
    return debug;
}

void Application::flushFiles() {
    for (const auto &entry: std::filesystem::directory_iterator("users")) {
        std::filesystem::remove(entry);
    }

    for (const auto &entry: std::filesystem::directory_iterator("blocks")) {
        if (entry.path() != "blocks/1.dat") {
            std::filesystem::remove(entry);
        }
    }
}
