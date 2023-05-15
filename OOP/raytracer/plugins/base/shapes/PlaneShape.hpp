/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PlaneShape.hpp
*/

#ifndef PLANESHAPE_HPP_
#define PLANESHAPE_HPP_

#include "AShape.hpp"

namespace raytracer::shapes {
    class PlaneShape : public AShape {
    public:
        explicit PlaneShape(plugins::Arguments args);
        ~PlaneShape() override = default;

        [[nodiscard]] std::vector<double> getIntersectionsWithRay(const Ray &ray) const override;
    private:
        utils::Vector _normal;
    };
}

#endif //PLANESHAPE_HPP_
