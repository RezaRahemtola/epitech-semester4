/*
** EPITECH PROJECT, 2023
** nts
** File description:
** And
*/

#include "components/gates/Or.hpp"

nts::component::Or::Or() : AGate(
        3,
        {
            {{True, True}, True},
            {{True, False}, True},
            {{True, Undefined}, True},
            {{False, True}, True},
            {{False, False}, False},
            {{False, Undefined}, Undefined},
            {{Undefined, True}, True},
            {{Undefined, False}, Undefined},
            {{Undefined, Undefined}, Undefined}
        }
)
{}
