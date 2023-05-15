/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** ConeShape.hpp
*/

#ifndef CONESHAPE_HPP_
#define CONESHAPE_HPP_

#include "AShape.hpp"

namespace raytracer::shapes {

    class ConeShape : public AShape {
    public:
        explicit ConeShape(plugins::Arguments args);
        ~ConeShape() override = default;

        [[nodiscard]] std::vector<double> getIntersectionsWithRay(const Ray &ray) const override;
    private:
        utils::Vector _end;
        double _radius;
    };
}

#endif //CONESHAPE_HPP_
