//
// Created by Martynas Skrebė on 2022-10-15.
//

#ifndef BLOCKCHAIN_TRANSACTIONSPOOL_H
#define BLOCKCHAIN_TRANSACTIONSPOOL_H


#include <unordered_map>
#include "Transaction.h"
#include "User.h"

class TransactionsPool {
    typedef std::unordered_map<std::string, Transaction> transactionsMap;

    transactionsMap transactions;
public:
    void createTransaction(User& sender, User& receiver, unsigned int amount);
    void generateTransactions(const std::function<User()>& randomUser);
    std::optional<Transaction> getTransaction(const std::string& id);
    std::pair<transactionsMap::iterator, transactionsMap::iterator> getRange(int from, int to);
    bool isEmpty();
    void erase(transactionsMap::key_type key);
    transactionsMap::size_type size();
};


#endif //BLOCKCHAIN_TRANSACTIONSPOOL_H
