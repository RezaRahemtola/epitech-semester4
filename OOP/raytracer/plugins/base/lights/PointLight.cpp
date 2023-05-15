/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PointLight.cpp
*/

#include "PointLight.hpp"

#include <utility>

namespace raytracer::lights {
    PointLight::PointLight(plugins::Arguments args) : APositionedLight(std::move(args))
    {}
}
