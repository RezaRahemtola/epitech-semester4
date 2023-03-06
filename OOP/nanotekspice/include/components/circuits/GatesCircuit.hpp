/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-dorian.moy
** File description:
** GatesCircuit.hpp
*/

#pragma once

#include <string>
#include "Circuit.hpp"

namespace nts::component {
    class GatesCircuit : public Circuit {
        public:
            explicit GatesCircuit(const std::string &gateName);
    };
}
