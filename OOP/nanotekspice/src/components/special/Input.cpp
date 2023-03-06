/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Input.cpp
*/

#include <utility>
#include "components/special/Input.hpp"


nts::component::Input::Input() : AEntry()
{
    this->pins[1] = Undefined;
}

void nts::component::Input::setNewState(nts::component::Tristate state)
{
    this->newState = state;
    this->needStateUpdate = true;
}

void nts::component::Input::simulate(std::size_t tick)
{
    // TODO: use tick
    (void) tick;

    if (!this->needStateUpdate)
        return;
    this->pins[1] = newState;
    this->needStateUpdate = false;
}
