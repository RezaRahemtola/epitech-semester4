/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** CylinderShape.cpp
*/

#include <cmath>
#include "CylinderShape.hpp"

namespace raytracer::shapes {
    CylinderShape::CylinderShape(plugins::Arguments args) : AShape(args)
    {
        try {
            if (!args.contains("end") || !args.contains("radius"))
                throw std::runtime_error("CylinderShape: missing arguments");
            _end = utils::mapToVector3<double>(std::any_cast<std::unordered_map<std::string, std::any>>(args["end"]));
            _radius = std::any_cast<double>(args["radius"]);
        } catch (const std::bad_any_cast &error) {
            throw std::runtime_error("CylinderShape: invalid argument type");
        }
    }

    std::vector<double> CylinderShape::getIntersectionsWithRay(const Ray &ray) const
    {
        const utils::Vector normalizedDirection = utils::normalize(ray.direction);
        const utils::Vector normalizedHeight = utils::normalize(_end - _position);
        const utils::Vector originBase = ray.origin - _position;
        const double vectorDirectionDotNormalizedHeight = utils::dotProduct(normalizedDirection, normalizedHeight);
        const double originBaseDotNormalizedHeight = utils::dotProduct(originBase, normalizedHeight);
        const double a = utils::dotProduct(normalizedDirection, normalizedDirection) -
                         (vectorDirectionDotNormalizedHeight * vectorDirectionDotNormalizedHeight);
        const double b = 2 * (utils::dotProduct(normalizedDirection, originBase) -
                              (vectorDirectionDotNormalizedHeight * originBaseDotNormalizedHeight));
        const double c = utils::dotProduct(originBase, originBase) -
                         (originBaseDotNormalizedHeight * originBaseDotNormalizedHeight) -
                         (_radius * _radius);
        if (b * b - 4 * a * c > 0) {
            const double t1 = (-b + std::sqrt(b * b - 4 * a * c)) / (2 * a);
            const double t2 = (-b - std::sqrt(b * b - 4 * a * c)) / (2 * a);
            return {t1, t2};
        } else if (b * b - 4 * a * c == 0 && utils::dotProduct(normalizedDirection, normalizedHeight) != 1)
            return {(-b / (2 * a))};
        else
            return {};
    }
}
