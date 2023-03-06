/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Nor
*/

#include "components/gates/Nor.hpp"

nts::component::Nor::Nor() : AGate(
        3,
        {
                {{True,      True},      False},
                {{True,      False},     False},
                {{True,      Undefined}, False},
                {{False,     True},      False},
                {{False,     False},     True},
                {{False,     Undefined}, Undefined},
                {{Undefined, True},      False},
                {{Undefined, False},     Undefined},
                {{Undefined, Undefined}, Undefined}
        }
)
{}
