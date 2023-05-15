/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Ray.hpp
*/

#ifndef RAY_HPP_
#define RAY_HPP_

#include "Utils.hpp"

namespace raytracer {
    struct Ray {
        utils::Vector origin;
        utils::Vector direction;
        utils::Vector color;
    };
}

#endif //RAY_HPP_
