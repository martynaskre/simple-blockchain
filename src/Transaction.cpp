//
// Created by Martynas Skrebė on 2022-10-13.
//

#include "Transaction.h"
#include "Hash.h"
#include <utility>
#include <sstream>

Transaction::Transaction(std::string sender, std::string receiver, std::time_t timestamp, unsigned int amount) {
    std::stringstream identifier;

    identifier << sender << receiver << timestamp << amount;

    this->id = hash(identifier.str());
    this->sender = std::move(sender);
    this->receiver = std::move(receiver);
    this->timestamp = timestamp;
    this->amount = amount;
}

void Transaction::changeAmount(unsigned int newAmount) {
    amount = newAmount;
}

std::string Transaction::getId() {
    return id;
}

std::string Transaction::getSender() {
    return sender;
}

std::string Transaction::getReceiver() {
    return receiver;
}

unsigned int Transaction::getAmount() const {
    return amount;
}

std::time_t Transaction::getTimestamp() const {
    return timestamp;
}
