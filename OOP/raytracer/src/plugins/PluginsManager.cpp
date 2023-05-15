/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Parsing
*/

#include <filesystem>
#include "PluginsManager.hpp"

namespace raytracer::plugins {
    void PluginsManager::load()
    {
        for (const auto &entry: std::filesystem::directory_iterator("./plugins")) {
            std::error_code ec;
            if (std::filesystem::is_directory(entry.path(), ec))
                continue;

            _plugins.emplace_back(entry.path());
            _plugins[_plugins.size() - 1].load("raytracerPluginEntrypoint");
        }
    }

    std::unique_ptr<lights::ILight> PluginsManager::createLight(const std::string &name, const Arguments &args) const
    {
        for (auto &loader: _plugins) {
            auto plugin = loader.get();
            try {
                return plugin->createLight(name, args);
            } catch (const UnknownPluginComponentError &error) {
                continue;
            };
        }
        throw UnknownPluginComponentError("Can't create light: Not found in plugins");
    }

    std::unique_ptr<shapes::IShape> PluginsManager::createShape(const std::string &name, const Arguments &args) const
    {
        for (auto &loader: _plugins) {
            auto plugin = loader.get();

            try {
                return plugin->createShape(name, args);
            } catch (const UnknownPluginComponentError &error) {
                continue;
            };
        }
        throw UnknownPluginComponentError("Can't create shape: Not found in plugins");
    }

    std::unique_ptr<render::ARenderer>
    PluginsManager::createRenderer(const std::string &name, const Arguments &args) const
    {
        for (auto &loader: _plugins) {
            auto plugin = loader.get();

            try {
                return plugin->createRenderer(name, args);
            } catch (const UnknownPluginComponentError &error) {
                continue;
            };
        }
        throw UnknownPluginComponentError("Can't create renderer: Not found in plugins");
    }

    std::unique_ptr<output::AOutputGenerator>
    PluginsManager::createOutput(const std::string &name, const Arguments &args) const
    {
        for (auto &loader: _plugins) {
            auto plugin = loader.get();

            try {
                return plugin->createOutput(name, args);
            } catch (const UnknownPluginComponentError &error) {
                continue;
            };
        }
        throw UnknownPluginComponentError("Can't create output: Not found in plugins");
    }
}
