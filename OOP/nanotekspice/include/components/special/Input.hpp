/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Input.hpp
*/

#pragma once

#include "AEntry.hpp"

namespace nts::component {
    class Input : public AEntry {
        public:
            Input();
            void simulate(std::size_t tick) override;

            void setNewState(Tristate state);
        protected:
            Tristate newState = Undefined;
            bool needStateUpdate = false;
    };
}
