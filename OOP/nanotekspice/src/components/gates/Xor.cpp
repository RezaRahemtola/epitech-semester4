/*
** EPITECH PROJECT, 2023
** nts
** File description:
** And
*/

#include "components/gates/Xor.hpp"

nts::component::Xor::Xor() : AGate(
        3,
        {
            {{True, True}, False},
            {{False, False}, False},
            {{True, False}, True},
            {{False, True}, True},
            {{True, Undefined}, Undefined},
            {{Undefined, True}, Undefined},
            {{False, Undefined}, Undefined},
            {{Undefined, False}, Undefined},
            {{Undefined, Undefined}, Undefined}
        }
)
{}
