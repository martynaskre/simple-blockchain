//
// Created by Martynas Skrebė on 2022-10-13.
//

#include "Manager.h"
#include <iostream>
#include "Utils/Logger.h"

void Manager::bootstrap() {
    Logger::setState(true);

    users.generateUsers();
    transactions.generateTransactions([this]() -> User {
        return users.getRandomUser();
    });
}
