/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** SFML
*/

#include "SFML.hpp"

extern "C" arcade::SFML *displayEntrypoint()
{
    return new arcade::SFML;
}

static const size_t WIDTH = 1920;
static const size_t HEIGHT = 1080;
static const size_t SIZE_X = 30;
static const size_t SIZE_Y = 25;

arcade::SFML::SFML()
{
    this->_window.create(sf::VideoMode(WIDTH, HEIGHT), "Arcade - SFML");
}

arcade::SFML::~SFML()
{
    this->_window.close();
}

std::string arcade::SFML::getFilepath(const arcade::common::SpriteType type)
{
    std::string filepath = "assets/";

    switch (type) {
        case common::SpriteType::PLAYER:
            filepath += "player.png";
            break;
        case common::SpriteType::BODY:
            filepath += "body.png";
            break;
        case common::SpriteType::WALL:
            filepath += "wall.png";
            break;
        case common::SpriteType::BONUS_A:
            filepath += "bonus_a.png";
            break;
        case common::SpriteType::BONUS_B:
            filepath += "bonus_b.png";
            break;
        case common::SpriteType::ENEMY:
            filepath += "enemy.png";
            break;
    }
    return (filepath);
}

void arcade::SFML::displaySprites(const std::vector<common::Sprite> &sprites)
{
    std::string filepath;
    std::string sprite;

    for (const auto &n: sprites) {
        filepath = getFilepath(n.type);
        if (_texture.loadFromFile(filepath)) {
            this->_sprite.setTexture(_texture);
            this->_sprite.setPosition(n.position.x * SIZE_X, n.position.y * SIZE_Y);
            this->_window.draw(_sprite);
        }
    }
}

void arcade::SFML::displayTexts(const std::vector<common::Text> &texts)
{
    for (const auto &n: texts) {
        if (_font.loadFromFile("assets/font.ttf")) {
            this->_text.setFont(_font);
            this->_text.setString(n.text);
            this->_text.setPosition(n.position.x * SIZE_X, n.position.y * SIZE_Y);
            this->_text.setCharacterSize(n.size);
            this->_window.draw(_text);
        }
    }
}

void arcade::SFML::playSound(const std::vector<common::Sound> &sounds)
{
    for (const auto &n: sounds) {
        (void) n;
    }
}

void arcade::SFML::display(const common::Data &data)
{
    this->_window.clear();
    displaySprites(data.sprites);
    displayTexts(data.texts);
    playSound(data.sounds);
    this->_window.display();
}

std::optional<arcade::common::Input> arcade::SFML::getInput()
{
    sf::Event event;

    while (this->_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return (common::Input::EXIT);
        if (event.type == sf::Event::KeyReleased) {
            switch (event.key.code) {
                case sf::Keyboard::Q:
                    return (common::Input::EXIT);
                case sf::Keyboard::Up:
                    return (common::Input::UP);
                case sf::Keyboard::Down:
                    return (common::Input::DOWN);
                case sf::Keyboard::Right:
                    return (common::Input::RIGHT);
                case sf::Keyboard::Left:
                    return (common::Input::LEFT);
                case sf::Keyboard::Escape:
                    return (common::Input::BACK_MENU);
                case sf::Keyboard::R:
                    return (common::Input::RESTART);

                case sf::Keyboard::T:
                    return (common::Input::ACTION_1);
                case sf::Keyboard::Y:
                    return (common::Input::ACTION_2);
                case sf::Keyboard::U:
                    return (common::Input::SPECIAL_1);
                case sf::Keyboard::I:
                    return (common::Input::SPECIAL_2);
                case sf::Keyboard::G:
                    return (common::Input::NEXT_GAME);
                case sf::Keyboard::D:
                    return (common::Input::NEXT_LIBRARY);
                default:
                    break;
            }
        }
    }
    return std::nullopt;
}
