/*
** EPITECH PROJECT, 2023
** nts
** File description:
** AInput.hpp
*/

#pragma once

#include "components/AComponent.hpp"

namespace nts::component {
    class AEntry : public AComponent {
        public:
            Tristate compute(std::size_t pin, std::size_t tick) final;
    };
}
