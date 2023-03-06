/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-dorian.moy
** File description:
** Circuit4071.hpp
*/

#pragma once

#include <string>
#include "GatesCircuit.hpp"

namespace nts::component {
    class Circuit4071 : public GatesCircuit {
        public:
            explicit Circuit4071() : GatesCircuit("or") {};
    };
}
