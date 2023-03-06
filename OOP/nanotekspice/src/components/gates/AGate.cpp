/*
** EPITECH PROJECT, 2023
** nts
** File description:
** AGate
*/

#include "components/gates/AGate.hpp"

nts::component::AGate::AGate(const std::size_t pinNumber, std::map<std::vector<Tristate>, Tristate> truthTable)
        : AComponent(), pinNumber(pinNumber), truthTable(std::move(truthTable))
{
    for (size_t i = 1; i <= this->pinNumber; ++i)
        this->pins[i] = Undefined;
}

nts::component::Tristate nts::component::AGate::compute(std::size_t pin, std::size_t tick)
{
    if (pin != this->pinNumber) {
        return AComponent::compute(pin, tick);
    }
    std::vector<Tristate> input;
    for (size_t i = 1; i < this->pinNumber; ++i) {
        this->compute(i, tick);
        input.push_back(this->pins[i]);
    }
    Tristate result = this->truthTable[input];
    this->pins[pin] = result;
    return result;
}
