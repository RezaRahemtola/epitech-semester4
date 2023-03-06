/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-dorian.moy
** File description:
** Circuit4030.hpp
*/

#pragma once

#include <string>
#include "GatesCircuit.hpp"

namespace nts::component {
    class Circuit4030 : public GatesCircuit {
        public:
            explicit Circuit4030() : GatesCircuit("xor") {};
    };
}
