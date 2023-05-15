/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PointLight.hpp
*/

#ifndef POINTLIGHT_HPP_
#define POINTLIGHT_HPP_

#include "APositionedLight.hpp"

namespace raytracer::lights {
    class PointLight : public APositionedLight {
        public:
            explicit PointLight(plugins::Arguments args);
    };
}

#endif //POINTLIGHT_HPP_
