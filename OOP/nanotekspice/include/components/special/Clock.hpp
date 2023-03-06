/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Input.hpp
*/

#pragma once

#include "Input.hpp"

namespace nts::component {
    class Clock : public Input {
        public:
            Clock();
            void simulate(std::size_t tick) final;
    };
}
