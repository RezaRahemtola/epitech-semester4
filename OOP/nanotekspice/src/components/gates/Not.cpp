/*
** EPITECH PROJECT, 2023
** nts
** File description:
** And
*/

#include "components/gates/Not.hpp"

nts::component::Not::Not() : AGate(
        2,
        {
            {{True}, False},
            {{False}, True},
            {{Undefined}, Undefined}
        }
)
{}
