/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PlaneShape.cpp
*/

#include <cmath>
#include "PlaneShape.hpp"

namespace raytracer::shapes {
    PlaneShape::PlaneShape(plugins::Arguments args)
            : AShape(args)
    {
        try {
            if (!args.contains("normal"))
                throw std::invalid_argument("PlaneShape: Missing position");
            _normal = utils::mapToVector3<double>(std::any_cast<std::unordered_map<std::string, std::any>>
                                                          (args["normal"]));
        } catch (std::bad_any_cast &e) {
            throw std::invalid_argument("PlaneShape: " + std::string(e.what()));
        }

        if (utils::dotProduct(_normal, _normal) == 0)
            throw std::invalid_argument("PlaneShape: Normal vector must not be zero");
        _normal = utils::normalize(_normal);
    }

    std::vector<double> PlaneShape::getIntersectionsWithRay(const Ray &ray) const
    {
        if (ray.direction == utils::Vector(0, 0, 0))
            throw std::invalid_argument("Ray direction must not be zero");

        utils::Vector normalizedDirection = utils::normalize(ray.direction);
        double denominator = utils::dotProduct(normalizedDirection, _normal);

        if (denominator == 0)
            return {};

        double magnitude = utils::dotProduct(_position - ray.origin, _normal) / denominator;

        if (magnitude < 0)
            return {};
        return {magnitude};
    }
}
