/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Camera
*/

#include "Camera.hpp"
#include <cmath>
#include <iostream>
#include "Utils.hpp"

namespace raytracer::render {
    Camera::Camera(
            sf::Vector2<size_t> resolution,
            utils::Vector position,
            utils::Vector rotation,
            double fieldOfView
    ) : _resolution(resolution), _position(position), _rotation(rotation), _fieldOfView(fieldOfView)
    {
    }

    std::vector<Ray> Camera::computeRays() const
    {
        double degree = (_fieldOfView / 2.0) * (M_PI / 180);
        double distanceWindow = (static_cast<double>(_resolution.y) / 2.0) / std::tan(degree);
        utils::Vector firstPixelVector = {
                -(static_cast<double>(_resolution.x) / 2.0),
                distanceWindow,
                (static_cast<double>(_resolution.y) / 2.0)
        };
        std::vector<Ray> rays;
        Ray tmpRay;
        Ray RotationRay;

        for (size_t y = 0; y < _resolution.y; y++) {
            for (size_t x = 0; x < _resolution.x; x++) {
                tmpRay.color = {0, 255, 0};
                tmpRay.direction = {
                        firstPixelVector.x + static_cast<double>(x),
                        firstPixelVector.y,
                        firstPixelVector.z - static_cast<double>(y)
                };
                RotationRay.direction = tmpRay.direction;
                if (_rotation.z != 0) {
                    degree = (_rotation.z / 2.0) * (M_PI / 180);
                    RotationRay.direction.x = (RotationRay.direction.x * std::cos(degree)) - (RotationRay.direction.y * std::sin(degree));
                    RotationRay.direction.y = (RotationRay.direction.x * std::sin(degree)) + (RotationRay.direction.y * std::cos(degree));
                    RotationRay.direction.z = RotationRay.direction.z;
                }
                if (_rotation.y != 0) {
                    degree = (_rotation.y / 2.0) * (M_PI / 180);
                    RotationRay.direction.x = (RotationRay.direction.x * std::cos(degree)) + (RotationRay.direction.z * std::sin(degree));
                    RotationRay.direction.y = RotationRay.direction.y;
                    RotationRay.direction.z = -(RotationRay.direction.x * std::sin(degree)) + (RotationRay.direction.z * std::cos(degree));
                }
                if (_rotation.x != 0) {
                    degree = (_rotation.x / 2.0) * (M_PI / 180);
                    RotationRay.direction.x = RotationRay.direction.x;
                    RotationRay.direction.y = (RotationRay.direction.y * std::cos(degree)) - (RotationRay.direction.z * std::sin(degree));
                    RotationRay.direction.z = -(RotationRay.direction.y * std::sin(degree)) + (RotationRay.direction.z * std::cos(degree));
                }
                tmpRay.direction = raytracer::utils::normalize(RotationRay.direction);
                tmpRay.origin = _position;
                rays.push_back(tmpRay);
            }
        }
        return rays;
    }

    const sf::Vector2<size_t> &Camera::getResolution() const
    {
        return _resolution;
    }

    CameraBuilder &CameraBuilder::setResolution(sf::Vector2<size_t> resolution)
    {
        _resolution = resolution;
        return *this;
    }

    CameraBuilder &CameraBuilder::setPosition(utils::Vector position)
    {
        _position = position;
        return *this;
    }

    CameraBuilder &CameraBuilder::setRotation(utils::Vector rotation)
    {
        _rotation = rotation;
        return *this;
    }

    CameraBuilder &CameraBuilder::setFieldOfView(double fieldOfView)
    {
        _fieldOfView = fieldOfView;
        return *this;
    }

    Camera CameraBuilder::build()
    {
        return {_resolution, _position, _rotation, _fieldOfView};
    }
}
