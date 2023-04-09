/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Core
*/

#include "Core.hpp"
#include <chrono>
#include <thread>
#include <iostream>

arcade::Core::Core(const std::string &initialLib) : gameIndex(0), displayIndex(0)
{
    std::string username;
    std::cout << "Enter your username: ";
    getline(std::cin, username);

    this->parse(initialLib);
    this->display.load(initialLib);
    unsigned long user_score = 0;

    if (!this->menu(user_score, username))
        return;

    while (true) {
        auto input = this->display.get()->getInput();

        switch (*input) {
            case common::Input::NEXT_GAME:
                this->nextGame();
                break;
            case common::Input::NEXT_LIBRARY:
                this->nextDisplay();
                break;
            case common::Input::RESTART:
                this->game.load(this->availableGames[this->gameIndex]);
                break;
            case common::Input::EXIT:
                return;
            case common::Input::BACK_MENU:
                user_score += this->game.get()->tick().score;
                if (!this->menu(user_score, username))
                    return;
                break;
            case common::Input::UP:
            case common::Input::DOWN:
            case common::Input::RIGHT:
            case common::Input::LEFT:
            case common::Input::ACTION_1:
            case common::Input::ACTION_2:
            case common::Input::SPECIAL_1:
            case common::Input::SPECIAL_2:
                this->game.get()->handleInput(*input);
                break;
            default:
                auto data = this->game.get()->tick();
                this->display.get()->display(data);
                break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

arcade::common::Data arcade::Core::setUpMenu(unsigned long user_score, std::string &username)
{
    arcade::common::Data data;

    data.score = user_score;
    data.texts.push_back({{27, 1}, "Your Score: " + std::to_string(user_score), 75});
    data.texts.push_back({{21, 7}, "Graphicals Libraries: Press I to switch", 60});
    for (size_t index = 0; index < this->availableDisplays.size(); index++) {
        float i = index;
        if (index == this->displayIndex)
            data.texts.push_back({{27, (1 * i) + 10}, "# " + this->availableDisplays[index], 50});
        else
            data.texts.push_back({{27, (1 * i) + 10}, this->availableDisplays[index], 50});
    }
    data.texts.push_back({{24, 17}, "Games Libraries: Press G to switch", 60});
    for (size_t index = 0; index != this->availableGames.size(); index++) {
        float i = index;
        if (index == this->gameIndex)
            data.texts.push_back({{27, (1 * i) + 20}, "# " + this->availableGames[index], 50});
        else
            data.texts.push_back({{27, (1 * i) + 20}, this->availableGames[index], 50});
    }
    data.texts.push_back({{27, 35}, "Username: " + username, 60});
    return (data);
}

bool arcade::Core::menu(unsigned long user_score, std::string &username) noexcept
{
    while (true) {
        auto input = this->display.get()->getInput();

        switch (*input) {
            case common::Input::EXIT:
                return false;
            case common::Input::BACK_MENU:
                this->game.load(this->availableGames[this->gameIndex]);
                this->display.load(this->availableDisplays[this->displayIndex]);
                return true;
            case common::Input::RESTART:
                return true;
            case common::Input::NEXT_GAME:
                this->nextGame();
                break;
            case common::Input::SPECIAL_2:
                this->loadDisplay();
                break;
            case common::Input::NEXT_LIBRARY:
                this->nextDisplay();
                break;
            default:
                auto data = setUpMenu(user_score, username);
                this->display.get()->display(data);
                break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void arcade::Core::loadDisplay()
{
    this->displayIndex++;
    size_t len = this->availableDisplays.size();

    if (this->displayIndex == len) {
        this->displayIndex = 0;
    }
}

void arcade::Core::nextDisplay()
{
    this->displayIndex++;
    size_t len = this->availableDisplays.size();

    if (this->displayIndex == len) {
        this->displayIndex = 0;
    }
    this->display.load(this->availableDisplays[this->displayIndex]);
}

void arcade::Core::nextGame()
{
    this->gameIndex++;
    size_t len = this->availableGames.size();

    if (this->gameIndex == len) {
        this->gameIndex = 0;
    }
    this->game.load(this->availableGames[this->gameIndex]);
}
