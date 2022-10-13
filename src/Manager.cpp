//
// Created by Martynas Skrebė on 2022-10-13.
//

#include "Manager.h"
#include "Pools/UsersPool.h"

void Manager::bootstrap() {
    UsersPool usersPool;

    usersPool.generateUsers();
}
