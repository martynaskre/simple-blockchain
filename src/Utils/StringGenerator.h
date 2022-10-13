//
// Created by Martynas Skrebė on 2022-10-13.
//

#ifndef BLOCKCHAIN_STRINGGENERATOR_H
#define BLOCKCHAIN_STRINGGENERATOR_H


#include <string>
#include <random>

class StringGenerator {
    typedef unsigned long long int64;

    int64 length;
    static std::random_device rd;
    static std::mt19937 mt;
    static std::uniform_int_distribution<int> dist;

public:
    StringGenerator& setLength(int64 len);

    std::string generate() const;
};


#endif //BLOCKCHAIN_STRINGGENERATOR_H
