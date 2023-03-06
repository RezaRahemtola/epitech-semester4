/*
** EPITECH PROJECT, 2023
** nts
** File description:
** AGate
*/

#pragma once

#include <map>
#include <vector>
#include "../AComponent.hpp"

namespace nts::component {
    class AGate : public AComponent {
        public:
            explicit AGate(std::size_t pinNumber, std::map<std::vector<Tristate>, Tristate> truthTable);

            Tristate compute(std::size_t pin, std::size_t tick) override;
        private:
            const std::size_t pinNumber;
            std::map<std::vector<Tristate>, Tristate> truthTable;
    };
}
