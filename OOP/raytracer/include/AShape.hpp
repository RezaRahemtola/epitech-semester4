/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** AShape.hpp
*/

#ifndef ASHAPE_HPP_
#define ASHAPE_HPP_

#include "IShape.hpp"

namespace raytracer::shapes {
    class AShape : public IShape {
    public:
        explicit AShape(plugins::Arguments args)
        {
            try {
                if (args.find("color") == args.end() || args.find("position") == args.end())
                    throw std::invalid_argument("AShape: Missing argument");
                _color = utils::mapToVector3<int>(std::any_cast<std::unordered_map<std::string, std::any>>
                                                          (args["color"]), {"r", "g", "b"});
                _position = utils::mapToVector3<double>(std::any_cast<std::unordered_map<std::string, std::any>>
                                                                (args["position"]));
            } catch (const std::bad_any_cast &error) {
                throw std::invalid_argument("AShape: Invalid argument type");
            }
        };

        virtual ~AShape() = default;

        [[nodiscard]] bool intersectsWithRay(const Ray &ray) const noexcept
        {
            return !(this->getIntersectionsWithRay(ray).empty());
        }

        [[nodiscard]] virtual std::vector<double> getIntersectionsWithRay(const Ray &ray) const = 0;

        [[nodiscard]] utils::Color getColor() const noexcept
        {
            return (_color);
        }

        [[nodiscard]] utils::Position getPosition() const noexcept
        {
            return (_position);
        }

    protected:
        utils::Position _position;
        utils::Color _color;
    };
};
#endif //ASHAPE_HPP_
