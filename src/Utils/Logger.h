//
// Created by Martynas Skrebė on 2022-10-15.
//

#ifndef BLOCKCHAIN_LOGGER_H
#define BLOCKCHAIN_LOGGER_H


#include <string>

class Logger {
    static bool enabled;

    static bool canBeLogged();
public:
    static void setState(bool isEnabled);
    static void info(const std::string& message);
    static void error(const std::string& message);
};


#endif //BLOCKCHAIN_LOGGER_H
