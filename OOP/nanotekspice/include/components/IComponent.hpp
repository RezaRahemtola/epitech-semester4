/*
** EPITECH PROJECT, 2023
** nts
** File description:
** IComponent.hpp
*/

#pragma once

#include <cstddef>
#include <memory>

namespace nts::component {
    enum Tristate {
        Undefined = -1,
        True = 1,
        False = 0
    };

    struct Link;

    class IComponent {
    public:
        virtual ~IComponent() = default;

        virtual void simulate(std::size_t tick) = 0;
        virtual Tristate compute(std::size_t pin, std::size_t tick) = 0;
        virtual void setLink(std::size_t pin, Link link) = 0;
        virtual Link getEffectiveLink(std::size_t pin) = 0;
    };

    struct Link {
        std::size_t pin;
        IComponent &component;
    };
}
