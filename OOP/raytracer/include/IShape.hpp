/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** AShape.hpp
*/

#ifndef ISHAPE_HPP_
#define ISHAPE_HPP_

#include <vector>
#include <SFML/Graphics.hpp>
#include "Ray.hpp"
#include "Plugin.hpp"
#include "Utils.hpp"

namespace raytracer::shapes {
    class IShape {
    public:
        virtual ~IShape() = default;

        [[nodiscard]] virtual bool intersectsWithRay(const Ray &ray) const noexcept = 0;
        [[nodiscard]] virtual std::vector<double> getIntersectionsWithRay(const Ray &ray) const = 0;
        [[nodiscard]] virtual utils::Color getColor() const noexcept = 0;
        [[nodiscard]] virtual utils::Position getPosition() const noexcept = 0;
    };
};
#endif //ISHAPE_HPP_
