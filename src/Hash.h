//
// Created by Martynas Skrebė on 2022-09-15.
//

#ifndef BLOCKCHAIN_HASH_H
#define BLOCKCHAIN_HASH_H


#include <string>

class Hash {
private:
    std::string string;

    unsigned int rotateRight(int toRotate, int rotateBy);
    unsigned int rotateLeft(int toRotate, int rotateBy);

public:
    Hash();
    explicit Hash(std::string str);
    explicit Hash(char *str);

    Hash& setString(std::string str);
    Hash& setString(char *str);

    std::string make();
};

std::string hash(std::string string);


#endif //BLOCKCHAIN_HASH_H
