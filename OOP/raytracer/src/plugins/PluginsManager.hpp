/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PluginsManager
*/

#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <any>
#include "ALight.hpp"
#include "AShape.hpp"
#include "APlugin.hpp"
#include "ARenderer.hpp"
#include "AOutputGenerator.hpp"
#include "DynamicLoader.hpp"

namespace raytracer::plugins {
    class PluginsManager {
    public:
        void load();

        [[nodiscard]] std::unique_ptr<lights::ILight> createLight(const std::string &name, const Arguments &args) const;
        [[nodiscard]] std::unique_ptr<shapes::IShape> createShape(const std::string &name, const Arguments &args) const;
        [[nodiscard]] std::unique_ptr<render::ARenderer>
        createRenderer(const std::string &name, const Arguments &args) const;
        [[nodiscard]] std::unique_ptr<output::AOutputGenerator>
        createOutput(const std::string &name, const Arguments &args) const;
    private:
        std::vector<DynamicLoader<APlugin>> _plugins;
    };
}
