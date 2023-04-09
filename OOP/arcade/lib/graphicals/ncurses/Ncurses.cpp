/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

static const int SIZE_X = 60;
static const int SIZE_Y = 40;

extern "C" arcade::Ncurses *displayEntrypoint()
{
    return new arcade::Ncurses;
}

arcade::Ncurses::Ncurses()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(false);
}

arcade::Ncurses::~Ncurses()
{
    endwin();
}

std::string arcade::Ncurses::getFilepath(const arcade::common::SpriteType type)
{
    std::string filepath = "assets/";

    switch (type) {
        case common::SpriteType::PLAYER:
            filepath += "player.txt";
            break;
        case common::SpriteType::BODY:
            filepath += "body.txt";
            break;
        case common::SpriteType::WALL:
            filepath += "wall.txt";
            break;
        case common::SpriteType::BONUS_A:
            filepath += "bonus_a.txt";
            break;
        case common::SpriteType::BONUS_B:
            filepath += "bonus_b.txt";
            break;
        case common::SpriteType::ENEMY:
            filepath += "enemy.txt";
            break;
    }
    return (filepath);
}

std::string arcade::Ncurses::loadSprite(const std::string &filepath)
{
    std::ifstream file(filepath);
    std::string res;
    std::string line;

    if (!file.good()) {
        return (res);
    }
    while (getline(file, line)) {
        res += line;
    }
    file.close();
    return (res);
}

void arcade::Ncurses::displaySprites(const std::vector<common::Sprite> &sprites)
{
    std::string filepath;
    std::string sprite;

    for (const auto &n: sprites) {
        filepath = getFilepath(n.type);
        sprite = loadSprite(filepath);
        if (!sprite.empty()) {
            mvprintw(n.position.y, n.position.x, sprite.c_str());
        }
    }
}

void arcade::Ncurses::displayTexts(const std::vector<common::Text> &texts)
{
    for (const auto &n: texts) {
        if (!n.text.empty()) {
            mvprintw(n.position.y, n.position.x, n.text.c_str());
        }
    }
}

void arcade::Ncurses::display(const common::Data &data)
{
    erase();
    if (getmaxx(stdscr) < SIZE_X || getmaxy(stdscr) < SIZE_Y) {
        printw("Please enlarge your terminal\n");
    } else {
        displaySprites(data.sprites);
        displayTexts(data.texts);
    }
    refresh();
}

std::optional<arcade::common::Input> arcade::Ncurses::getInput()
{
    int touch = getch();

    if (touch == -1)
        return std::nullopt;
    switch (static_cast<Keyboard>(touch)) {
        case Keyboard::QUIT:
            return (common::Input::EXIT);
        case Keyboard::UP:
            return (common::Input::UP);
        case Keyboard::DOWN:
            return (common::Input::DOWN);
        case Keyboard::RIGHT:
            return (common::Input::RIGHT);
        case Keyboard::LEFT:
            return (common::Input::LEFT);
        case Keyboard::ESCAPE:
            return (common::Input::BACK_MENU);
        case Keyboard::R:
            return (common::Input::RESTART);

        case Keyboard::T:
            return (common::Input::ACTION_1);
        case Keyboard::Y:
            return (common::Input::ACTION_2);
        case Keyboard::U:
            return (common::Input::SPECIAL_1);
        case Keyboard::I:
            return (common::Input::SPECIAL_2);
        case Keyboard::NEXT_GAME:
            return (common::Input::NEXT_GAME);
        case Keyboard::NEXT_LIB:
            return (common::Input::NEXT_LIBRARY);
        default:
            break;
    }
    return std::nullopt;
}
