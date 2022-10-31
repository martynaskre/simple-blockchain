//
// Created by Martynas Skrebė on 2022-10-17.
//

#include "Cli.h"
#include "Utils/Application.h"

int main(int argc, char *argv[]) {
    Application::setDebug(false);

    Cli cli;

    cli.run(argc, argv);

    return 0;
}