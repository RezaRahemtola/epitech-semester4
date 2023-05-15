/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Scene.hpp
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <vector>
#include <memory>
#include "AShape.hpp"
#include "ALight.hpp"
#include "ARenderer.hpp"
#include "AOutputGenerator.hpp"
#include "camera/Camera.hpp"

namespace raytracer {
    class Scene {
    public:
        Scene(
                std::vector<std::unique_ptr<raytracer::shapes::IShape>> &shapes,
                std::vector<std::unique_ptr<raytracer::lights::ILight>> &lights,
                std::unique_ptr<render::ARenderer> renderer,
                std::unique_ptr<raytracer::output::AOutputGenerator> outputGenerator,
                render::Camera camera
        );
        ~Scene() = default;

        void render() const;

        [[nodiscard]] const std::vector<std::unique_ptr<raytracer::shapes::IShape>> &getShapes() const;
        [[nodiscard]] const std::vector<std::unique_ptr<raytracer::lights::ILight>> &getLights() const;
        [[nodiscard]] const render::Camera &getCamera() const;
    private:
        std::vector<std::unique_ptr<raytracer::shapes::IShape>> _shapes;
        std::vector<std::unique_ptr<raytracer::lights::ILight>> _lights;
        std::unique_ptr<raytracer::render::ARenderer> _renderer;
        std::unique_ptr<raytracer::output::AOutputGenerator> _outputGenerator;
        render::Camera _camera;
    };

    class SceneBuilder {
    public:
        SceneBuilder() = default;
        ~SceneBuilder() = default;

        SceneBuilder &addShape(std::unique_ptr<shapes::IShape> shape);
        SceneBuilder &addLight(std::unique_ptr<lights::ILight> light);
        SceneBuilder &setRenderer(std::unique_ptr<raytracer::render::ARenderer> renderer);
        SceneBuilder &setOutputGenerator(std::unique_ptr<raytracer::output::AOutputGenerator> outputGenerator);
        SceneBuilder &setCamera(render::Camera camera);
        Scene build();
    private:
        std::vector<std::unique_ptr<raytracer::shapes::IShape>> _shapes;
        std::vector<std::unique_ptr<raytracer::lights::ILight>> _lights;
        std::unique_ptr<raytracer::render::ARenderer> _renderer;
        std::unique_ptr<raytracer::output::AOutputGenerator> _outputGenerator;
        std::unique_ptr<render::Camera> _camera;
    };
}

#endif //SCENE_HPP_
