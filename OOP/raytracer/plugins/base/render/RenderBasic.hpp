/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-raytracer-reza.rahemtola
** File description:
** ARendererBasic
*/

#ifndef RENDERBASIC_HPP_
#define RENDERBASIC_HPP_

#include "ARenderer.hpp"
#include "../../../src/Scene.hpp"

namespace raytracer::render {

    struct ShapeInfo {
        utils::Color color;
        utils::Position pos;
        double t;
    };

    class RenderBasic : public ARenderer {
    public:
        explicit RenderBasic(const plugins::Arguments &args);
        [[nodiscard]] std::vector<utils::Color> render(const Scene &scene) const override;

        utils::Color getPixelColor(raytracer::Ray ray, const Scene &scene) const;
        utils::Position getLightPosition(const std::unique_ptr<raytracer::lights::ILight> &light) const;

        utils::Color
        applyShadow(utils::Color shapeColor, utils::Color lightColor, utils::Vector direction, utils::Vector n) const;
        utils::Color applyIntensity(utils::Color shapeColor, utils::Color lightColor, double intensity) const;
        ShapeInfo getShapeColor(raytracer::Ray ray, const Scene &scene) const;
    };
}

#endif /* !RENDERBASIC_HPP_ */
