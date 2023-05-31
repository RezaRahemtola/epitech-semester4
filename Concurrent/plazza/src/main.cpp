/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** main
*/

#include <iostream>
#include "configuration/Configuration.hpp"
#include "MessageQueue.hpp"
#include "reception/Reception.hpp"

int main(int argc, char **argv)
{
    std::vector<std::string> arguments(argv, argv + argc);

    try {
        plazza::configuration::Configuration configuration(arguments);
        plazza::reception::Reception reception(configuration);
        reception.open();
    } catch (const plazza::configuration::ConfigurationException &exception) {
        std::cerr << exception.what() << std::endl << std::endl;
        plazza::configuration::Configuration::showHelp(arguments[0]);
        return 84;
    }
    return 0;
}
