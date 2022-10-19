//
// Created by Martynas Skrebė on 2022-10-19.
//

#ifndef BLOCKCHAIN_APPLICATION_H
#define BLOCKCHAIN_APPLICATION_H


#include "Manager.h"

class Application {
    static bool debug;
    static const std::vector<std::pair<std::string, std::string>> commands;

    void flushFiles();
public:
    void run(int argc, char *argv[]);
    void printHelp();

    static void setDebug(bool isDebug);
    static bool runningInDebug();
};


#endif //BLOCKCHAIN_APPLICATION_H
