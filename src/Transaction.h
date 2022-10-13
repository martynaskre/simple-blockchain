//
// Created by Martynas Skrebė on 2022-10-13.
//

#ifndef BLOCKCHAIN_TRANSACTION_H
#define BLOCKCHAIN_TRANSACTION_H


#include <string>

class Transaction {
    std::string id;
    std::string sender;
    std::string receiver;
    unsigned int amount;

public:
    Transaction(std::string sender, std::string receiver, unsigned int amount);
    void changeAmount(unsigned int newAmount);

    std::string getId();
    std::string getSender();
    std::string getReceiver();
    unsigned int getAmount() const;
};


#endif //BLOCKCHAIN_TRANSACTION_H
