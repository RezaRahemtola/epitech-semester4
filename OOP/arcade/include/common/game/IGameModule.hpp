/*
** EPITECH PROJECT, 2023
** Arcade-Common
** File description:
** IGameModule.hpp
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include "../Data.hpp"
#include "../Input.hpp"

namespace arcade::common {
    class IGameModule {
        public:
            virtual ~IGameModule() = default;

            virtual void handleInput(Input in) = 0;
            virtual Data &tick() = 0;
    };
}

#endif
