/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Main.cpp
*/

#include <iostream>
#include <cstring>
#include "NTS.hpp"
#include "Parsing.hpp"
#include "Simulator.hpp"
#include "components/gates/Gates.hpp"

static void displayUsage()
{
    std::cout << "Usage: ./nanotekspice config.nts" << std::endl
              << "config.nts:\t Path to the configuration file with chipsets and links." << std::endl;
}

int main(int argc, char const *argv[])
{
    nts::component::Circuit circuit;
    nts::Parser parser(circuit);
    nts::Simulator simulator(circuit);

    if (argc != 2) {
        std::cerr << "Invalid number of arguments." << std::endl;
        return 84;
    }
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        displayUsage();
        return 0;
    }

    try {
        // TODO: return in function and save it in circuit
        parser.createCircuitFromFile(argv[1]);
    } catch (const std::exception &except) {
        std::cerr << except.what() << std::endl;
        return 84;
    };
    simulator.run();
    return 0;
}
