/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Snake
*/

#include <algorithm>
#include <iostream>
#include "Snake.hpp"

static const size_t MOVING_SPEED = 1;
static const size_t MAP_X = 60;
static const size_t MAP_Y = 40;

namespace arcade {
    extern "C" Snake *gameEntrypoint()
    {
        return new Snake;
    }

    Snake::Snake() : AGameModule(), distrib_x(2, 58), distrib_y(2, 38), gen(std::random_device()())
    {
        float y = 0;
        float x = 0;
        std::string tmp = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                         aaab                             x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "x                                                          x\n"
                          "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\0";
        for (size_t i = 0; tmp[i] != '\0'; i++) {
            if (tmp[i] == '\n') {
                x = 0;
                y++;
            } else if (tmp[i] == 'x') {
                this->wall.push_back({{x, y}, common::SpriteType::WALL});
                x++;
            } else if (tmp[i] == 'a') {
                this->player.insert(this->player.begin(), {{x, y}, common::SpriteType::BODY});
                x++;
            } else if (tmp[i] == 'b') {
                this->player.insert(this->player.begin(), {{x, y}, common::SpriteType::PLAYER});
                x++;
            } else {
                x++;
            }
        }
        if (!this->fruit.position.y) {
            this->popFruit();
        }
        this->direction = arcade::common::Input::RIGHT;
    }

    void Snake::handleInput(arcade::common::Input in)
    {
        if (in == arcade::common::Input::UP) {
            if (this->direction == arcade::common::Input::DOWN) {
                return;
            }
            this->direction = in;
        } else if (in == arcade::common::Input::DOWN) {
            if (this->direction == arcade::common::Input::UP) {
                return;
            }
            this->direction = in;
        } else if (in == arcade::common::Input::LEFT) {
            if (this->direction == arcade::common::Input::RIGHT) {
                return;
            }
            this->direction = in;
        } else if (in == arcade::common::Input::RIGHT) {
            if (this->direction == arcade::common::Input::LEFT) {
                return;
            }
            this->direction = in;
        }
    }

    bool Snake::postFruit()
    {
        size_t pos_head_x = this->player.front().position.x;
        size_t pos_head_y = this->player.front().position.y;

        if (this->fruit.position.x == pos_head_x && this->fruit.position.y == pos_head_y) {
            return true;
        }
        return false;
    }

    bool Snake::postWall()
    {
        float x = this->player.front().position.x;
        float y = this->player.front().position.y;

        arcade::common::Position w{x, y};
        auto it = std::find_if(this->wall.begin(), this->wall.end(), [&w](const arcade::common::Sprite &sprite) {
            return sprite.position.x == w.x && sprite.position.y == w.y;
        });
        if (it != this->wall.end()) {
            return true;
        }
        return false;
    }

    bool Snake::postSnake()
    {
        size_t pos_head_x = this->player.front().position.x;
        size_t pos_head_y = this->player.front().position.y;

        for (size_t i = 1; i < this->player.size(); i++) {
            if (this->player[i].position.x == pos_head_x &&
                this->player[i].position.y == pos_head_y) {
                return true;
            }
        }
        return false;
    }

    void Snake::move()
    {
        const size_t MOVEMENT = MOVING_SPEED;
        common::Position old = this->player[0].position;
        common::Position current{};

        for (size_t i = 1; i < this->player.size(); i++) {
            current = this->player[i].position;
            this->player[i].position = old;
            old = current;
        }
        switch (this->direction) {
            case arcade::common::Input::UP:
                this->player[0].position.y -= MOVEMENT;
                break;
            case arcade::common::Input::DOWN:
                this->player[0].position.y += MOVEMENT;
                break;
            case arcade::common::Input::LEFT:
                this->player[0].position.x -= MOVEMENT;
                break;
            case arcade::common::Input::RIGHT:
                this->player[0].position.x += MOVEMENT;
                break;
            default:
                break;
        }
        if (this->postSnake() || this->postWall()) {
            this->isGameOver();
            return;
        }
        if (this->postFruit()) {
            this->popFruit();
            this->increaseBody(old);
            this->scoreUp();
        }
    }

    void Snake::popFruit()
    {
        float x = distrib_x(gen);
        float y = distrib_y(gen);

        this->fruit = {{x, y}, common::SpriteType::BONUS_A};
    }

    void Snake::increaseBody(common::Position pos)
    {
        arcade::common::Sprite body = {pos, common::SpriteType::BODY};

        this->player.push_back(body);
    }

    common::Data &Snake::tick()
    {
        this->move();
        data.sprites.clear();
        data.texts.clear();
        data.score = this->score;
        if (this->gameOver) {
            data.texts.push_back({{MAP_X / 2, MAP_Y / 2}, "Game Over", 30});
        } else {
            for (auto sprite: this->player) {
                data.sprites.push_back(sprite);
            }
            for (auto sprite: this->wall) {
                data.sprites.push_back(sprite);
            }
            data.sprites.push_back(this->fruit);
        }
        data.mapHeight = MAP_Y;
        data.mapWidth = MAP_X;
        return data;
    }
}
