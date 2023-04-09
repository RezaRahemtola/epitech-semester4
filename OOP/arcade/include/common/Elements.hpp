/*
** EPITECH PROJECT, 2023
** Arcade-Common
** File description:
** Elements.hpp
*/

#ifndef ELEMENTS_HPP_
#define ELEMENTS_HPP_

#include <string>

namespace arcade::common {
    enum class SpriteType {
        PLAYER,
        BODY,
        WALL,
        BONUS_A,
        BONUS_B,
        ENEMY,
    };

    enum class SoundType {

    };

    struct Position {
        float x;
        float y;
    };

    struct Sprite {
        Position position;
        SpriteType type;
    };

    struct Sound {
        std::size_t volume;
        SoundType type;
    };

    struct Text {
        Position position;
        std::string text;
        std::size_t size;
    };
}

#endif
