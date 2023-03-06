/*
** EPITECH PROJECT, 2023
** nts
** File description:
** And
*/

#include "components/gates/And.hpp"

nts::component::And::And()
: AGate(
        3,
        {
            {{True, True}, True},
            {{False, False}, False},
            {{True, False}, False},
            {{False, True}, False},
            {{True, Undefined}, Undefined},
            {{Undefined, True}, Undefined},
            {{False, Undefined}, False},
            {{Undefined, False}, False},
            {{Undefined, Undefined}, Undefined}
        }
)
{
}
