//
// Created by Martynas Skrebė on 2022-10-15.
//

#include "Logger.h"
#include <iostream>
#include "Utils/Color.h"

bool Logger::enabled = true;

void Logger::setState(bool isEnabled) {
    enabled = isEnabled;
}

bool Logger::canBeLogged() {
    return enabled;
}

void Logger::info(const std::string& message) {
    if (!canBeLogged()) {
        return;
    }

    std::cout << Color::MAGENTA << "[INFO] " << Color::RESET << message << std::endl;
}

void Logger::error(const std::string &message) {
    if (!canBeLogged()) {
        return;
    }

    std::cout << Color::RED << "[ERROR] " << Color::RESET << message << std::endl;
}
