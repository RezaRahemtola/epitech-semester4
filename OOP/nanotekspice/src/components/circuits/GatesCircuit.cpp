/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-dorian.moy
** File description:
** GatesCircuit.cpp
*/

#include "components/circuits/GatesCircuit.hpp"

nts::component::GatesCircuit::GatesCircuit(const std::string &gateName)
{
    this->initializePins({1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13});

    this->createComponent(gateName, "1");
    this->createComponent(gateName, "2");
    this->createComponent(gateName, "3");
    this->createComponent(gateName, "4");

    this->createInternalLink(1, {1, this->operator[]("1")});
    this->createInternalLink(2, {2, this->operator[]("1")});
    this->createInternalLink(3, {3, this->operator[]("1")});

    this->createInternalLink(5, {1, this->operator[]("2")});
    this->createInternalLink(6, {2, this->operator[]("2")});
    this->createInternalLink(4, {3, this->operator[]("2")});

    this->createInternalLink(8, {1, this->operator[]("3")});
    this->createInternalLink(9, {2, this->operator[]("3")});
    this->createInternalLink(10, {3, this->operator[]("3")});

    this->createInternalLink(12, {1, this->operator[]("4")});
    this->createInternalLink(13, {2, this->operator[]("4")});
    this->createInternalLink(11, {3, this->operator[]("4")});
}
