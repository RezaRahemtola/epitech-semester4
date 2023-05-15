/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** ALight.hpp
*/

#ifndef ALIGHT_HPP_
#define ALIGHT_HPP_

#include "ILight.hpp"

namespace raytracer::lights {
    class ALight : public ILight {
    public:
        explicit ALight(plugins::Arguments args)
        {
            try {
                if (!args.contains("color") || !args.contains("intensity"))
                    throw std::invalid_argument("ALight: Missing argument");
                _color = utils::mapToVector3<int>(std::any_cast<std::unordered_map<std::string, std::any>>
                                                          (args["color"]), {"r", "g", "b"});
                _intensity = std::any_cast<double>(args["intensity"]);
            } catch (const std::bad_any_cast &error) {
                throw std::invalid_argument("ALight: Invalid argument type");
            }
        };
        virtual ~ALight() = default;

        [[nodiscard]] const utils::Color &getColor() const override
        {
            return _color;
        }

        [[nodiscard]] double getIntensity() const override
        {
            return _intensity;
        }

    private:
        utils::Color _color;
        double _intensity;
    };
}

#endif //ALIGHT_HPP_
