/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** SDL2
*/

#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../../include/common/display/IDisplayModule.hpp"

#pragma once

namespace arcade {
    class SDL2 : public common::IDisplayModule {
        public:
            SDL2();
            ~SDL2() override;

            void display(const common::Data &data) override;
            std::optional<common::Input> getInput() override;
        private:
            void displaySprites(const std::vector<common::Sprite> &sprites);
            void displayTexts(const std::vector<common::Text> &texts);
            void playSound(const std::vector<common::Sound> &sounds);

            int getSpriteTexture(const arcade::common::SpriteType type);
            void loadSprite();

            SDL_Window *_window;
            SDL_Event _event;
            SDL_Renderer *_rend;
            std::vector<SDL_Texture *> _texture;
            SDL_Texture *_text;
            SDL_Surface *_surface;
            SDL_Rect _dest;
            TTF_Font *_font;
            SDL_Color _white;
    };

    extern "C" SDL2 *displayEntrypoint();
}
