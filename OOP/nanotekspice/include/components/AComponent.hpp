/*
** EPITECH PROJECT, 2023
** nts
** File description:
** IComponent.hpp
*/

#pragma once

#include <unordered_map>
#include "IComponent.hpp"

namespace nts::component {
    class AComponent : public IComponent {
    public:
        void simulate(std::size_t tick) override;
        Tristate compute(std::size_t pin, std::size_t tick) override;
        void setLink(std::size_t pin, Link link) override;
        Link getEffectiveLink(std::size_t pin) override;

        Tristate getPinSate(size_t pin);
    protected:
        size_t currentTick = 0;
        std::unordered_map<std::size_t, Tristate> pins;
        std::unordered_map<std::size_t, Link> links;
    };
}
