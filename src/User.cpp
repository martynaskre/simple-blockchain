//
// Created by Martynas Skrebė on 2022-10-13.
//

#include "User.h"
#include "Hash.h"
#include "Manager.h"
#include <utility>
#include <fstream>
#include <algorithm>

User::User(std::string name, std::string passphrase, unsigned int balance) {
    this->name = std::move(name);
    this->public_key = hash(std::move(passphrase));
    this->balance = balance;

    save();
}

void User::setName(std::string newName) {
    this->name = std::move(newName);

    save();
}

void User::setBalance(unsigned int newBalance) {
    if (balance - newBalance < 0) {
        throw std::invalid_argument("User balance can not be negative");
    }

    this->balance = newBalance;

    save();
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

void User::save() {
    if (!Manager::runningInDebug()) {
        std::ofstream writer;

        writer.open("users/" + getPublicKey() + ".dat");

        writer << getName() << std::endl << getBalance() << std::endl;

        writer.close();
    }
}

User User::fromFile(std::string filename) {
    std::ifstream read(filename);

    filename.erase(filename.begin(), filename.begin() + 6);
    filename.erase(filename.end() - 4, filename.end());

    std::string name;
    unsigned int balance;

    read >> name >> balance;

    return {balance, filename, name};
}

User::User(unsigned int balance, std::string public_key, std::string name): public_key(std::move(public_key)), name(std::move(name)), balance(balance) {}
