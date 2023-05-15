/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Scene.cpp
*/

#include "Scene.hpp"
#include "ARenderer.hpp"
#include "AOutputGenerator.hpp"

namespace raytracer {
    Scene::Scene(std::vector<std::unique_ptr<raytracer::shapes::IShape>> &shapes,
                 std::vector<std::unique_ptr<raytracer::lights::ILight>> &lights,
                 std::unique_ptr<render::ARenderer> renderer,
                 std::unique_ptr<raytracer::output::AOutputGenerator> outputGenerator,
                 render::Camera camera
    )
            : _shapes(std::move(shapes)), _lights(std::move(lights)), _renderer(std::move(renderer)),
              _outputGenerator(std::move(outputGenerator)), _camera(camera)
    {}

    void Scene::render() const
    {
        const auto &[width, height] = _camera.getResolution();
        _outputGenerator->makeOutput(_renderer->render(*this), height, width);
    }

    const std::vector<std::unique_ptr<raytracer::shapes::IShape>> & Scene::getShapes() const
    {
        return _shapes;
    }

    const std::vector<std::unique_ptr<raytracer::lights::ILight>> & Scene::getLights() const
    {
        return _lights;
    }

    const render::Camera &Scene::getCamera() const
    {
        return _camera;
    }

    SceneBuilder &SceneBuilder::addShape(std::unique_ptr<shapes::IShape> shape)
    {
        _shapes.push_back(std::move(shape));
        return *this;
    }

    SceneBuilder &SceneBuilder::addLight(std::unique_ptr<lights::ILight> light)
    {
        _lights.push_back(std::move(light));
        return *this;
    }

    SceneBuilder &
    SceneBuilder::setRenderer(std::unique_ptr<render::ARenderer> renderer)
    {
        _renderer = std::move(renderer);
        return *this;
    }

    SceneBuilder &
    SceneBuilder::setOutputGenerator(std::unique_ptr<output::AOutputGenerator> outputGenerator)
    {
        _outputGenerator = std::move(outputGenerator);
        return *this;
    }

    Scene SceneBuilder::build()
    {
        return {
                _shapes,
                _lights,
                std::move(_renderer),
                std::move(_outputGenerator),
                *_camera
        };
    }

    SceneBuilder &SceneBuilder::setCamera(render::Camera camera)
    {
        _camera = std::make_unique<render::Camera>(camera);
        return *this;
    }
}
