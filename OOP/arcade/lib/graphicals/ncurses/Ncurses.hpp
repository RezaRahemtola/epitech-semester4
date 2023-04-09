/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** Ncurse
*/

#pragma once

#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "../../../include/common/display/IDisplayModule.hpp"
#include "../../../include/common/Elements.hpp"

namespace arcade {

    enum class Keyboard {
        UP = KEY_UP,
        DOWN = KEY_DOWN,
        RIGHT = KEY_RIGHT,
        LEFT = KEY_LEFT,
        ESCAPE = 27,
        R = 'r',
        T = 't',
        Y = 'y',
        U = 'u',
        I = 'i',
        NEXT_GAME = 'g',
        NEXT_LIB = 'd',
        QUIT = 'q',
    };

    class Ncurses : public common::IDisplayModule {
        public:
            Ncurses();
            ~Ncurses() override;

            void display(const common::Data &data) override;
            std::optional<common::Input> getInput() override;
        private:
            void displaySprites(const std::vector<common::Sprite> &sprites);
            void displayTexts(const std::vector<common::Text> &texts);

            std::string getFilepath(arcade::common::SpriteType type);
            std::string loadSprite(const std::string &filepath);

    };

    extern "C" Ncurses *displayEntrypoint();
}
