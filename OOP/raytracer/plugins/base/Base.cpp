/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Base.cpp
*/

#include "Base.hpp"
#include "lights/PointLight.hpp"
#include "shapes/ConeShape.hpp"
#include "shapes/CylinderShape.hpp"
#include "shapes/PlaneShape.hpp"
#include "shapes/SphereShape.hpp"
#include "render/RenderBasic.hpp"
#include "output/PPMOutputGenerator.hpp"
#include "output/SFMLOutputGenerator.hpp"

namespace raytracer::plugins {
    extern "C" Plugin *raytracerPluginEntrypoint()
    {
        return new Plugin;
    }

    Plugin::Plugin()
    {
        // Add elements here with the following format:
        // FACTORY.setElement<BASE_TYPE>(NAME)
        // example:
        // _lightFactory.setElement<lights::PointLight>("point");
        _lightFactory.setElement<lights::PointLight>("point");

        _shapeFactory.setElement<shapes::ConeShape>("cone");
        _shapeFactory.setElement<shapes::CylinderShape>("cylinder");
        _shapeFactory.setElement<shapes::PlaneShape>("plane");
        _shapeFactory.setElement<shapes::SphereShape>("sphere");

        _renderFactory.setElement<render::RenderBasic>("basic");
        _outputFactory.setElement<output::PPMOutputGenerator>("ppm");
        _outputFactory.setElement<output::SFMLOutputGenerator>("sfml");
    }
}
