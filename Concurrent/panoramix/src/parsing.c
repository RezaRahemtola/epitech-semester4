/*
** EPITECH PROJECT, 2023
** panoramix
** File description:
** parsing
*/

#include <stdlib.h>
#include <stdbool.h>

static bool isnumber(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

bool are_params_valid(int argc, const char *argv[])
{
    if (argc != 5 || !isnumber(argv[1]) || !isnumber(argv[2]) ||
    !isnumber(argv[3]) || !isnumber(argv[4]) || atoi(argv[1]) == 0)
        return false;
    return true;
}
