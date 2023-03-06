/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-tekspice-dorian.moy
** File description:
** Circuit4069.cpp
*/

#include "components/circuits/Circuit4069.hpp"


nts::component::Circuit4069::Circuit4069()
{
    this->initializePins({1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13});

    this->createComponent("not", "A");
    this->createComponent("not", "B");
    this->createComponent("not", "C");
    this->createComponent("not", "D");
    this->createComponent("not", "E");
    this->createComponent("not", "F");

    this->createInternalLink(1, {1, this->operator[]("A")});
    this->createInternalLink(2, {2, this->operator[]("A")});

    this->createInternalLink(3, {1, this->operator[]("B")});
    this->createInternalLink(4, {2, this->operator[]("B")});

    this->createInternalLink(5, {1, this->operator[]("C")});
    this->createInternalLink(6, {2, this->operator[]("C")});

    this->createInternalLink(9, {1, this->operator[]("D")});
    this->createInternalLink(8, {2, this->operator[]("D")});

    this->createInternalLink(11, {1, this->operator[]("E")});
    this->createInternalLink(10, {2, this->operator[]("E")});

    this->createInternalLink(13, {1, this->operator[]("F")});
    this->createInternalLink(12, {2, this->operator[]("F")});
}
