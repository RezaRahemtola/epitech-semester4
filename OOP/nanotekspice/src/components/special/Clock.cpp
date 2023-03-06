/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Input.cpp
*/

#include <utility>
#include "components/special/Clock.hpp"


nts::component::Clock::Clock() : Input()
{
}

void nts::component::Clock::simulate(std::size_t tick)
{
    if (this->needStateUpdate) {
        Input::simulate(tick);
        return;
    }

    nts::component::Tristate current = this->pins[1];
    if (current == Undefined)
        return;
    this->pins[1] = (current == nts::component::True) ? nts::component::False : nts::component::True;
}
