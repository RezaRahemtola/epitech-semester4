/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-dorian.moy
** File description:
** Circuit4011.hpp
*/

#pragma once

#include <string>
#include "GatesCircuit.hpp"

namespace nts::component {
    class Circuit4011 : public GatesCircuit {
        public:
            explicit Circuit4011() : GatesCircuit("nand") {};
    };
}
