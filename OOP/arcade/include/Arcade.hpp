/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Arcade
*/

#pragma once

#include <stdexcept>

namespace arcade {
    class Error : public std::exception {
        public:
            explicit Error(std::string text) : text(std::move(text))
            {};

            [[nodiscard]] const char *what() const noexcept override
            {
                return this->text.c_str();
            };

        private:
            std::string text;
    };
}
