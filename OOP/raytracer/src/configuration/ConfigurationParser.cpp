/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** write_file
*/

#include <iostream>
#include "ConfigurationParser.hpp"

namespace raytracer::configuration_parser {
    raytracer::Scene ConfigurationParser::parse(const std::string &filePath)
    {
        raytracer::SceneBuilder sceneBuilder;
        libconfig::Config configuration;

        configuration.readFile(filePath.c_str());

        const libconfig::Setting &scene = configuration.lookup("scene");
        const libconfig::Setting &camera = configuration.lookup("camera");
        const libconfig::Setting &shapes = scene.lookup("shapes");
        const libconfig::Setting &lights = scene.lookup("lights");

        for (const auto &shapeSettings: shapes) {
            std::string type = shapeSettings.lookup("type");
            auto shapesSettingsMap = settingToMap(shapeSettings);
            sceneBuilder.addShape(_pluginsManager.createShape(type, shapesSettingsMap));
        }

        for (const auto &lightSettings: lights) {
            std::string type = lightSettings.lookup("type");
            auto lightSettingsMap = settingToMap(lightSettings);
            sceneBuilder.addLight(_pluginsManager.createLight(type, lightSettingsMap));
        }

        sceneBuilder.setRenderer(_pluginsManager.createRenderer(scene.lookup("renderer"), {}));
        sceneBuilder.setOutputGenerator(_pluginsManager.createOutput(scene.lookup("output"), {}));

        try {
            this->setCamera(camera, sceneBuilder);
        } catch (std::bad_any_cast const &error) {
            std::cerr << "Invalid camera settings" << std::endl;
            throw libconfig::SettingTypeException(camera);
        }
        return sceneBuilder.build();
    }

    void ConfigurationParser::setCamera(const libconfig::Setting &camera, raytracer::SceneBuilder &sceneBuilder) const
    {
        auto cameraSettingsMap = settingToMap(camera);
        auto resolution = utils::mapToVector2<int>(any_cast<utils::AnyMap>(cameraSettingsMap["resolution"]),
                                                   {"width", "height"});
        if (resolution.x <= 0 || resolution.y <= 0)
            throw std::invalid_argument("Invalid resolution");
        sceneBuilder.setCamera(
                {
                        {
                                static_cast<size_t>(resolution.x),
                                static_cast<size_t>(resolution.y)
                        },
                        utils::mapToVector3<double>(
                                any_cast<utils::AnyMap>(cameraSettingsMap["position"])
                        ),
                        utils::mapToVector3<double>(
                                any_cast<utils::AnyMap>(cameraSettingsMap["rotation"])
                        ),
                        camera.lookup("fov")
                }
        );
    }

    ConfigurationParser::ConfigurationParser(const plugins::PluginsManager &pluginsManager)
            : _pluginsManager(pluginsManager)
    {}

    std::unordered_map<std::string, std::any> ConfigurationParser::settingToMap(const libconfig::Setting &setting) const
    {
        if (!setting.isGroup())
            throw std::invalid_argument("Setting is not a group");

        std::unordered_map<std::string, std::any> map;

        for (const auto &settingItem: setting) {
            std::string key = settingItem.getName();
            std::any value;

            if (settingItem.isGroup())
                value = settingToMap(settingItem);
            else if (settingItem.isScalar())
                value = parseValue(settingItem);
            else
                throw std::invalid_argument("Setting is not a scalar or a group");

            map.insert({key, value});
        }
        return map;
    }

    std::any ConfigurationParser::parseValue(const libconfig::Setting &setting)
    {
        switch (setting.getType()) {
            case libconfig::Setting::TypeInt:
            case libconfig::Setting::TypeInt64:
                return static_cast<int>(setting.getParent().lookup(setting.getName()));
            case libconfig::Setting::TypeFloat:
                return static_cast<double>(setting.getParent().lookup(setting.getName()));
            case libconfig::Setting::TypeString:
                return static_cast<std::string>(setting.getParent().lookup(setting.getName()));
            case libconfig::Setting::TypeBoolean:
                return static_cast<bool>(setting.getParent().lookup(setting.getName()));
            case libconfig::Setting::TypeGroup:
            case libconfig::Setting::TypeArray:
            case libconfig::Setting::TypeList:
            case libconfig::Setting::TypeNone:
            default:
                throw std::invalid_argument("Setting is not a scalar");
        }
    }
}
