/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <vector>
#include <map>
#include <cmath>
#include <SFML/System/Vector2.hpp>

#include "Ray.hpp"
#include "Utils.hpp"

namespace raytracer::render {
    class Camera {
    public:
        Camera(sf::Vector2<size_t> resolution, utils::Vector position, utils::Vector rotation,
               double fieldOfView);
        ~Camera() = default;

        [[nodiscard]] std::vector<Ray> computeRays() const;

        [[nodiscard]] const sf::Vector2<size_t> &getResolution() const;
    private:
        sf::Vector2<size_t> _resolution;
        utils::Vector _position;
        utils::Vector _rotation;
        double _fieldOfView;
    };

    class CameraBuilder {
    public:
        CameraBuilder() = default;
        ~CameraBuilder() = default;

        CameraBuilder &setResolution(sf::Vector2<size_t> resolution);
        CameraBuilder &setPosition(utils::Vector position);
        CameraBuilder &setRotation(utils::Vector rotation);
        CameraBuilder &setFieldOfView(double fieldOfView);
        Camera build();
    private:
        sf::Vector2<size_t> _resolution{};
        utils::Vector _position{};
        utils::Vector _rotation{};
        double _fieldOfView{};
    };
}

#endif /* !CAMERA_HPP_ */
