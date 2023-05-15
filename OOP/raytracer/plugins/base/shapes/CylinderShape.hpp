/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** CylinderShape.hpp
*/

#ifndef CYLINDERSHAPE_HPP_
#define CYLINDERSHAPE_HPP_

#include "AShape.hpp"

namespace raytracer::shapes {
    class CylinderShape : public AShape {
    public:
        explicit CylinderShape(plugins::Arguments args);
        ~CylinderShape() override = default;

        [[nodiscard]] std::vector<double> getIntersectionsWithRay(const Ray &ray) const override;
    private:
        utils::Vector _end;
        double _radius;
    };
}

#endif //CYLINDERSHAPE_HPP_
