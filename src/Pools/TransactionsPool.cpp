//
// Created by Martynas Skrebė on 2022-10-15.
//

#include "TransactionsPool.h"
#include <utility>
#include <iostream>
#include "Utils/NumberGenerator.h"
#include "User.h"
#include "Utils/Logger.h"
#include "Hash.h"

void TransactionsPool::createTransaction(User& sender, User& receiver, unsigned int amount) {
    if (sender.getBalance() < amount) {
        Logger::error(sender.getPublicKey() + " tried to send " + std::to_string(amount) + " while having only " + std::to_string(sender.getBalance()));

        return;
    }

    Transaction transaction = Transaction(sender.getPublicKey(), receiver.getPublicKey(), std::time(nullptr), amount);

    std::string hashCheck = hash(sender.getPublicKey() + receiver.getPublicKey() + std::to_string(transaction.getTimestamp()) + std::to_string(transaction.getAmount()));

    if (transaction.getId() != hashCheck) {
        Logger::error("Invalid transaction hash");

        return;
    }

    if (transactions.contains(transaction.getId())) {
        Logger::error("Integrity fault, transaction with same ID already exists " + transaction.getId());

        return;
    }

    transactions.insert(std::make_pair(transaction.getId(), transaction));

    Logger::info("New transaction was registered " + transaction.getId());
}

void TransactionsPool::generateTransactions(const std::function<User()>& randomUser) {
    NumberGenerator numberGenerator = {};

    int toGenerate = 500;

    for (int i = 0; i < toGenerate; i++) {
        User sender = randomUser();
        User receiver = randomUser();

        if (sender.getPublicKey() == receiver.getPublicKey()) {
            while (sender.getPublicKey() == receiver.getPublicKey()) {
                receiver = randomUser();
            }
        }

        createTransaction(sender, receiver, numberGenerator.setLength(1, 1000).generate());
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

std::pair<TransactionsPool::transactionsMap::iterator, TransactionsPool::transactionsMap::iterator> TransactionsPool::getRange(int from, int to) {
    std::pair<TransactionsPool::transactionsMap::iterator, TransactionsPool::transactionsMap::iterator> bounds;

    bounds.first = std::next(std::begin(transactions), from);
    bounds.second = std::next(std::begin(transactions), to);

    return bounds;
}

bool TransactionsPool::isEmpty() {
    return transactions.empty();
}

void TransactionsPool::erase(transactionsMap::key_type key) {
    transactions.erase(key);
}

TransactionsPool::transactionsMap::size_type TransactionsPool::size() {
    return transactions.size();
}
