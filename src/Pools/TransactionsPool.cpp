//
// Created by Martynas Skrebė on 2022-10-15.
//

#include "TransactionsPool.h"
#include <utility>
#include <iostream>
#include "Utils/NumberGenerator.h"
#include "User.h"
#include "Utils/Logger.h"

void TransactionsPool::createTransaction(std::string sender, std::string receiver, unsigned int amount) {
    Transaction transaction = Transaction(std::move(sender), std::move(receiver), amount);

    transactions.insert(std::make_pair(transaction.getId(), transaction));

    Logger::info("New transaction was registered " + transaction.getId());
}

void TransactionsPool::generateTransactions(const std::function<User()>& randomUser) {
    NumberGenerator numberGenerator = {};

    int toGenerate = 10000;

    for (int i = 0; i < toGenerate; i++) {
        createTransaction(randomUser().getPublicKey(), randomUser().getPublicKey(), numberGenerator.setLength(1, 1000).generate());
    }
}

std::optional<Transaction> TransactionsPool::getTransaction(const std::string &id) {
    try {
        return transactions.at(id);
    } catch (const std::out_of_range& e) {
        //
    }

    return std::nullopt;
}
