/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Plugin
*/

#pragma once

#include <unordered_map>
#include <string>
#include <any>
#include <stdexcept>
#include "Utils.hpp"

namespace raytracer::plugins {
    using Arguments = utils::AnyMap;

    class UnknownPluginComponentError : public std::exception {
    public:
        explicit UnknownPluginComponentError(std::string text) : text(std::move(text))
        {};

        [[nodiscard]] const char *what() const noexcept override
        {
            return this->text.c_str();
        };

    private:
        std::string text;
    };
}
