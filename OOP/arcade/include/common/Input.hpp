/*
** EPITECH PROJECT, 2023
** Arcade-Common
** File description:
** Input.hpp
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

namespace arcade::common {
    enum class Input {
        // Joystick / Arrows
        UP,
        DOWN,
        RIGHT,
        LEFT,

        // Buttons
        ACTION_1,
        ACTION_2,
        SPECIAL_1,
        SPECIAL_2,

        // Special inputs
        NEXT_LIBRARY,
        NEXT_GAME,
        RESTART,
        BACK_MENU,
        EXIT,
    };
}

#endif
