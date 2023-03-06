/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Simulator
*/

#include <sstream>
#include <iostream>
#include <string>
#include <csignal>
#include "Simulator.hpp"

nts::Simulator::Simulator(nts::component::Circuit &circuit) : circuit(circuit)
{
    this->commands["exit"] = &Simulator::exit;
    this->commands["display"] = &Simulator::display;
    this->commands["simulate"] = &Simulator::simulate;
    this->commands["loop"] = &Simulator::loop;
}

void nts::Simulator::exit()
{
    std::cin.setstate(std::ios::eofbit);
}

void nts::Simulator::display()
{
    for (const auto &outputName: this->circuit.getOutputNames()) {
        this->circuit[outputName].compute(1, this->currentTick);
    }

    std::cout << "tick: " << this->currentTick << std::endl;
    this->circuit.display();
}

void nts::Simulator::simulate()
{
    this->currentTick++;

    for (const auto &inputName: this->circuit.getInputNames()) {
        this->circuit[inputName].simulate(this->currentTick);
    }
}

static bool isInterrupted = false;

void signalHandler(int signal)
{
    (void) signal;
    isInterrupted = true;
}

void nts::Simulator::loop()
{
    signal(SIGINT, signalHandler);
    while (!isInterrupted) {
        this->simulate();
        this->display();
    }
    signal(SIGINT, SIG_DFL);
}

void nts::Simulator::changeInputComponent()
{
    std::string name;
    std::string value;
    nts::component::Tristate state;
    std::stringstream ss(this->input);

    getline(ss, name, '=');
    getline(ss, value);

    if (value == "U") {
        state = nts::component::Undefined;
    } else if (value == "0") {
        state = nts::component::False;
    } else if (value == "1") {
        state = nts::component::True;
    } else {
        return;
    }
    this->circuit.setInputValue(name, state);
}

bool nts::Simulator::getUserInput()
{
    if (std::cin.eof())
        return false;
    std::cout << "> ";
    getline(std::cin, this->input);
    if (std::cin.eof())
        return false;
    return true;
}

void nts::Simulator::run()
{
    while (this->getUserInput()) {
        if (this->commands.find(this->input) != this->commands.end())
            (this->*this->commands[this->input])();
        this->changeInputComponent();
    }
}
