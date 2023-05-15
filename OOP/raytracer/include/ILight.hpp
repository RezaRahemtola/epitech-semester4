/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** ALight.hpp
*/

#ifndef ILIGHT_HPP_
#define ILIGHT_HPP_

#include <SFML/System/Vector3.hpp>
#include <string>
#include "Plugin.hpp"
#include "Utils.hpp"

namespace raytracer::lights {
    class ILight {
    public:
        virtual ~ILight() = default;

        [[nodiscard]] virtual const utils::Color &getColor() const = 0;
        [[nodiscard]] virtual double getIntensity() const = 0;
    };
}

#endif //ILIGHT_HPP_
