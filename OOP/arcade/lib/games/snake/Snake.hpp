/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-reza.rahemtola
** File description:
** snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <random>
#include "../AGameModule.hpp"

namespace arcade {
    class Snake : public AGameModule {
        public:
            Snake();
            void handleInput(arcade::common::Input in) override;
            common::Data &tick() override;
        private:
            void popFruit();
            void increaseBody(common::Position pos);
            void move();
            bool postSnake();
            bool postFruit();
            bool postWall();

            arcade::common::Sprite fruit{};
            std::vector<arcade::common::Sprite> wall;
            common::Data data;
            arcade::common::Input direction;
            std::uniform_int_distribution<> distrib_x;
            std::uniform_int_distribution<> distrib_y;
            std::mt19937 gen;
    };

    extern "C" Snake *gameEntrypoint();
}

#endif /* !SNAKE_HPP_ */
