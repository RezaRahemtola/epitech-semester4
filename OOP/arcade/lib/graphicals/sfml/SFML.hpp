/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** SFML
*/

#pragma once

#include <fstream>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../../include/common/display/IDisplayModule.hpp"

namespace arcade {
    class SFML : public common::IDisplayModule {
        public:
            SFML();
            ~SFML() override;

            void display(const common::Data &data) override;
            std::optional<common::Input> getInput() override;
        private:
            void displaySprites(const std::vector<common::Sprite> &sprites);
            void displayTexts(const std::vector<common::Text> &texts);
            void playSound(const std::vector<common::Sound> &sounds);

            std::string getFilepath(const arcade::common::SpriteType type);
            std::string loadSprite(const std::string filepath);

            sf::RenderWindow _window;

            sf::Sprite _sprite;
            sf::Texture _texture;

            sf::Text _text;
            sf::Font _font;

            sf::Music _music;

    };

    extern "C" SFML *displayEntrypoint();
}
