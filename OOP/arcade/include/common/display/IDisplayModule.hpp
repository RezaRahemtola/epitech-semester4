/*
** EPITECH PROJECT, 2023
** Arcade-Common
** File description:
** IDisplayModule.hpp
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <optional>
#include "../Data.hpp"
#include "../Elements.hpp"
#include "../Input.hpp"

namespace arcade::common {
    class IDisplayModule {
        public:
            virtual ~IDisplayModule() = default;

            virtual void display(const Data &data) = 0;
            virtual std::optional<Input> getInput() = 0;
    };
}

#endif
