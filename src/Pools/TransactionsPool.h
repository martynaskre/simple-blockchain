//
// Created by Martynas Skrebė on 2022-10-15.
//

#ifndef BLOCKCHAIN_TRANSACTIONSPOOL_H
#define BLOCKCHAIN_TRANSACTIONSPOOL_H


#include <unordered_map>
#include "Transaction.h"
#include "User.h"

class TransactionsPool {
    std::unordered_map<std::string, Transaction> transactions;
public:
    void createTransaction(std::string sender, std::string receiver, unsigned int amount);
    void generateTransactions(const std::function<User()>& randomUser);
    std::optional<Transaction> getTransaction(const std::string& id);
};


#endif //BLOCKCHAIN_TRANSACTIONSPOOL_H
