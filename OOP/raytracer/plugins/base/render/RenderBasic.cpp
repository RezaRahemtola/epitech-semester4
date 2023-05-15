/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** ARendererBasic
*/

#include "RenderBasic.hpp"
#include "../output/SFMLOutputGenerator.hpp"
#include "../output/PPMOutputGenerator.hpp"
#include "Ray.hpp"
#include "../../../src/Scene.hpp"
#include "APositionedLight.hpp"

namespace raytracer::render {

    void displayPicture(const std::vector<sf::Vector3i> &picture)
    {
        raytracer::output::PPMOutputGenerator ppmOutputGenerator({});
        raytracer::output::SFMLOutputGenerator sfmlOutputGenerator({});

        ppmOutputGenerator.makeOutput(picture, 1080, 1920);
        sfmlOutputGenerator.makeOutput(picture, 1080, 1920);
        std::cout << "Complete !" << std::endl;
    }

    ShapeInfo RenderBasic::getShapeColor(raytracer::Ray ray, const Scene &scene) const
    {
        ShapeInfo result;
        utils::Color tmpColor = {0, 0, 0};
        utils::Position tmpPos = {0, 0, 0};
        double t = 10000;
        double tmpT = 0;

        for (const auto &shape: scene.getShapes()) {
            if (shape->intersectsWithRay(ray)) {
                auto data = shape->getIntersectionsWithRay(ray);
                tmpT = data.front();
                if (tmpT > data.back())
                    tmpT = data.back();
                if (tmpT < t) {
                    t = tmpT;
                    tmpColor = shape->getColor();
                    tmpPos = shape->getPosition();
                }
            }
        }
        result.color = tmpColor;
        result.pos = tmpPos;
        result.t = t;
        return (result);
    }

    utils::Color RenderBasic::applyIntensity(utils::Color shapeColor, utils::Color lightColor, double intensity) const
    {
        utils::Color color;

        color.x = shapeColor.x * (intensity / 100);
        color.y = shapeColor.y * (intensity / 100);
        color.z = shapeColor.z * (intensity / 100);

        return (color);
    }

    utils::Color RenderBasic::applyShadow(utils::Color shapeColor, utils::Color lightColor, utils::Vector direction,
                                          utils::Vector n) const
    {
        utils::Color color;
        double lambert = (direction.x * n.x) + (direction.y * n.y) + (direction.z * n.z) / 100;

        color.x = shapeColor.x * lambert;
        color.y = shapeColor.y * lambert;
        color.z = shapeColor.z * lambert;

        return (color);
    }

    utils::Position RenderBasic::getLightPosition(const std::unique_ptr<raytracer::lights::ILight> &light) const
    {
        raytracer::lights::ILight *parent = light.get();
        auto *child = dynamic_cast<raytracer::lights::APositionedLight *>(parent);

        if (child == nullptr)
            return {};
        return child->getPosition();
    }

    utils::Color RenderBasic::getPixelColor(raytracer::Ray ray, const Scene &scene) const
    {
        ShapeInfo interShape = getShapeColor(ray, scene);
        ShapeInfo interWithLight;
        raytracer::Ray rayLight;
        utils::Position distance;
        utils::Vector scaled = {interShape.t * ray.direction.x, interShape.t * ray.direction.y,
                                interShape.t * ray.direction.z};
        utils::Vector newOrigin = ray.origin + scaled;
        utils::Vector n = newOrigin - interShape.pos;
        double temp = n.x * n.x + n.y * n.y + n.z * n.z;
        double t;

        if (temp == 0)
            return (interShape.color);
        temp = 1 / sqrtf(temp);
        n = {n.x * temp, n.y * temp, n.z * temp};
        for (const auto &light: scene.getLights()) {
            distance = getLightPosition(light) - newOrigin;
            if (distance.x * n.x + distance.y * n.y + distance.z * n.z <= 0.0f)
                continue;
            t = std::sqrt((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z));
            if (t <= 0.0f)
                continue;
            rayLight = {newOrigin, {distance.x * (1 / t), distance.y * (1 / t), 1}, {0, 0, 0}};
            for (const auto &shape: scene.getShapes()) {
                if (shape->intersectsWithRay(rayLight)) {
                    interWithLight = getShapeColor(rayLight, scene);
                    interShape.color = applyIntensity(interShape.color, interWithLight.color, light->getIntensity());
                    interShape.color = applyShadow(interShape.color, light->getColor(), rayLight.direction, n);
                }
            }
        }
        return (interShape.color);
    }

    std::vector<utils::Color> RenderBasic::render(const Scene &scene) const
    {
        std::vector<utils::Color> picture;

        for (const auto &ray: scene.getCamera().computeRays())
            picture.push_back(getPixelColor(ray, scene));
        return picture;
    }

    RenderBasic::RenderBasic([[maybe_unused]] const plugins::Arguments &args)
    {}

}
