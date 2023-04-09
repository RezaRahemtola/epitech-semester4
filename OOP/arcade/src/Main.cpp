/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Main
*/

#include <iostream>
#include "Core.hpp"

static void displayUsage()
{
    std::cout << "Usage: ./arcade lib.so" << std::endl
              << "lib.so:\t Path to a graphical library for initial usage." << std::endl;
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        std::cerr << "Invalid number of arguments: got " + std::to_string(argc) + " but expected 2." << std::endl;
        displayUsage();
        return 84;
    }
    std::string lib = argv[1];
    if (lib == "-h" || lib == "--help") {
        displayUsage();
        return 0;
    }

    try {
        arcade::Core core(lib);
    } catch (const std::exception &except) {
        std::cerr << except.what() << std::endl;
        return 84;
    };
    return 0;
}
