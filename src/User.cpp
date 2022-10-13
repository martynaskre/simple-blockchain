//
// Created by Martynas Skrebė on 2022-10-13.
//

#include "User.h"
#include "Hash.h"
#include <utility>

User::User(std::string name, std::string passphrase, unsigned int balance) {
    this->name = std::move(name);
    this->public_key = hash(std::move(passphrase));
    this->balance = balance;
}

void User::setName(std::string newName) {
    this->name = std::move(newName);
}

void User::setBalance(int newBalance) {
    if (balance - newBalance < 0) {
        throw std::invalid_argument("User balance can not be negative");
    }

    this->balance = newBalance;
}

std::string User::getName() {
    return name;
}

std::string User::getPublicKey() {
    return public_key;
}

unsigned int User::getBalance() const {
    return balance;
}
