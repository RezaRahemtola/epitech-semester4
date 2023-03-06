/*
** EPITECH PROJECT, 2023
** nts
** File description:
** AComponent.cpp
*/

#include <utility>

#include "components/AComponent.hpp"
#include "NTS.hpp"

void nts::component::AComponent::simulate(std::size_t tick)
{
    if (this->currentTick == tick)
        return;
}

void nts::component::AComponent::setLink(std::size_t pin, nts::component::Link link)
{
    if (this->links.contains(pin))
        throw nts::Error("Simulation: Trying to link a pin that is already linked.");
    this->links.insert({pin, link});
}

nts::component::Link nts::component::AComponent::getEffectiveLink(std::size_t pin)
{
    return Link{pin, *this};
}

nts::component::Tristate nts::component::AComponent::compute(std::size_t pin, std::size_t tick)
{
    if (this->currentTick == tick)
        return this->pins[pin];
    if (!this->links.contains(pin))
        return Undefined;
    auto link = this->links.at(pin);
    this->pins[pin] = link.component.compute(link.pin, tick);
    return this->pins[pin];
}

nts::component::Tristate nts::component::AComponent::getPinSate(size_t pin)
{
    return this->pins[pin];
}
