/*
** EPITECH PROJECT, 2023
** nts
** File description:
** AEntry
*/

#include "components/special/AEntry.hpp"

nts::component::Tristate nts::component::AEntry::compute(std::size_t pin, std::size_t tick)
{
    (void) tick;
    return this->pins[pin];
}
