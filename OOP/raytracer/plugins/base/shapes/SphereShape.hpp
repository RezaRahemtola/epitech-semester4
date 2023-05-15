/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** SphereShape.hpp
*/

#ifndef SPHERESHAPE_HPP_
#define SPHERESHAPE_HPP_

#include "AShape.hpp"

namespace raytracer::shapes {
    class SphereShape : public AShape {
    public:
        explicit SphereShape(plugins::Arguments args);
        ~SphereShape() override = default;

        [[nodiscard]] std::vector<double> getIntersectionsWithRay(const Ray &ray) const override;

    private:
        double _radius;
    };
}

#endif //SPHERESHAPE_HPP_
