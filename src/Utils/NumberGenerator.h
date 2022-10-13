//
// Created by Martynas Skrebė on 2022-10-13.
//

#ifndef BLOCKCHAIN_NUMBERGENERATOR_H
#define BLOCKCHAIN_NUMBERGENERATOR_H


#include <string>
#include <random>


class NumberGenerator {
    int from;
    int to;
    static std::random_device rd;
    static std::mt19937 mt;

public:
    NumberGenerator& setLength(int from, int to);

    int generate() const;
};


#endif //BLOCKCHAIN_NUMBERGENERATOR_H
