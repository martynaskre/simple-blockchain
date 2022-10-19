//
// Created by Martynas Skrebė on 2022-10-13.
//

#ifndef BLOCKCHAIN_USER_H
#define BLOCKCHAIN_USER_H


#include <string>
#include <nlohmann/json.hpp>

class User {
    std::string name;
    std::string public_key;
    unsigned int balance;

    void save();
    User(unsigned int balance, std::string public_key, std::string name);
public:
    User(std::string name, std::string passphrase, unsigned int balance);
    void setName(std::string newName);
    void setBalance(unsigned int newBalance);

    std::string getName();
    std::string getPublicKey();
    unsigned int getBalance() const;

    std::string to_json();
    static User from_json(nlohmann::json& json);
};


#endif //BLOCKCHAIN_USER_H
