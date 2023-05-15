/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** SphereShape.cpp
*/

#include <cmath>
#include "SphereShape.hpp"
#include "Utils.hpp"

namespace raytracer::shapes {
    SphereShape::SphereShape(plugins::Arguments args) : AShape(args)
    {
        try {
            if (args.find("radius") == args.end())
                throw std::invalid_argument("SphereShape: Missing radius argument");
            _radius = std::any_cast<double>(args["radius"]);
        } catch (std::bad_any_cast &error) {
            throw std::invalid_argument("SphereShape: Invalid radius argument type");
        }
        if (_radius <= 0)
            throw std::invalid_argument("Radius must be positive");
    }

    std::vector<double> SphereShape::getIntersectionsWithRay(const Ray &ray) const
    {
        if (ray.direction == utils::Vector(0, 0, 0))
            throw std::invalid_argument("Ray direction must not be zero");

        utils::Vector normalizedDirection = utils::normalize(ray.direction);
        utils::Vector q = ray.origin - _position;
        double a = utils::dotProduct(normalizedDirection, normalizedDirection);
        double b = 2 * utils::dotProduct(normalizedDirection, q);
        double c = utils::dotProduct(q, q) - _radius * _radius;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0)
            return {};
        else if (discriminant == 0)
            return {(-b / (2 * a))};
        else {
            double t1 = (-b + std::sqrt(discriminant)) / (2 * a);
            double t2 = (-b - std::sqrt(discriminant)) / (2 * a);
            return {t1, t2};
        }
    }

}
