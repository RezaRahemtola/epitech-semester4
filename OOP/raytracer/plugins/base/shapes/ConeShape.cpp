/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** ConeShape.cpp
*/

#include <cmath>
#include "ConeShape.hpp"

namespace raytracer::shapes {

    ConeShape::ConeShape(plugins::Arguments args) : AShape(args)
    {
        try {
            if (!args.contains("end") || args.contains("radius"))
                throw std::invalid_argument("ConeShape: Missing argument");
            _end = utils::mapToVector3<double>(std::any_cast<std::unordered_map<std::string, std::any>>(args["end"]));
            _radius = std::any_cast<double>(args["radius"]);
        } catch (const std::bad_any_cast &error) {
            throw std::invalid_argument("ConeShape: Invalid argument type");
        }
    }

    std::vector<double> ConeShape::getIntersectionsWithRay(const Ray &ray) const
    {
        const utils::Vector normalizedDirection = utils::normalize(ray.direction);
        const utils::Vector height = _position - _end;
        const utils::Vector normalizedHeight = utils::normalize(height);
        const double radiusFromHeight = (_radius * _radius) / utils::normOf(height) * utils::normOf(height);
        const utils::Vector originEnd = ray.origin - _end;
        const auto vectorDirectionDotNormalizedHeight = utils::dotProduct(normalizedDirection, normalizedHeight);
        const double a =
                utils::dotProduct(normalizedDirection, normalizedDirection) -
                radiusFromHeight * (vectorDirectionDotNormalizedHeight * vectorDirectionDotNormalizedHeight) -
                (vectorDirectionDotNormalizedHeight * vectorDirectionDotNormalizedHeight);
        const double b = 2 * (utils::dotProduct(normalizedDirection, originEnd) -
                              radiusFromHeight *
                              (vectorDirectionDotNormalizedHeight * utils::dotProduct(originEnd, normalizedHeight)) -
                              (vectorDirectionDotNormalizedHeight * utils::dotProduct(originEnd, normalizedHeight)));
        const double c = utils::dotProduct(originEnd, originEnd) -
                         radiusFromHeight * (utils::dotProduct(originEnd, normalizedHeight) *
                                             utils::dotProduct(originEnd, normalizedHeight)) -
                         (utils::dotProduct(originEnd, normalizedHeight) *
                          utils::dotProduct(originEnd, normalizedHeight));
        if (b * b - 4 * a * c > 0) {
            const double t1 = (-b + sqrtf(b * b - 4 * a * c)) / (2 * a);
            const double t2 = (-b - sqrtf(b * b - 4 * a * c)) / (2 * a);
            return {t1, t2};
        }
        if (b * b - 4 * a * c == 0) {
            const double cosAlpha = utils::normOf(height) / (std::sqrt(utils::normOf(height) * utils::normOf(height) +
                                                                       _radius * _radius));
            if (std::abs(utils::dotProduct(normalizedDirection, normalizedHeight)) != cosAlpha) {
                return {(-b / (2 * a))};
            }
        }
        return {};
    }
}
