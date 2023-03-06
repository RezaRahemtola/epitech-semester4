/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Nand
*/

#include "components/gates/Nand.hpp"

nts::component::Nand::Nand()
        : AGate(
        3,
        {
                {{True,      True},      False},
                {{False,     False},     True},
                {{True,      False},     True},
                {{False,     True},      True},
                {{True,      Undefined}, Undefined},
                {{Undefined, True},      Undefined},
                {{False,     Undefined}, True},
                {{Undefined, False},     True},
                {{Undefined, Undefined}, Undefined}
        }
)
{
}
