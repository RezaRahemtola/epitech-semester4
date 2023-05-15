/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** APositionedLight.hpp
*/

#ifndef APOSITIONEDLIGHT_HPP_
#define APOSITIONEDLIGHT_HPP_

#include "ALight.hpp"

namespace raytracer::lights {
    class APositionedLight : public ALight {
    public:
        explicit APositionedLight(plugins::Arguments args) : ALight(args)
        {
            try {
                if (!args.contains("position"))
                    throw std::invalid_argument("APositionedLight: Missing position argument");
                _position = utils::mapToVector3<double>(
                        std::any_cast<std::unordered_map<std::string, std::any>>(args["position"])
                );
            } catch (const std::bad_any_cast &error) {
                throw std::invalid_argument("APositionedLight: Invalid position argument type");
            }

        };
        ~APositionedLight() override = default;

        [[nodiscard]] const utils::Vector &getPosition() const
        {
            return _position;
        }

    private:
        utils::Vector _position;
    };
}

#endif //APOSITIONEDLIGHT_HPP_
