/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** parser
*/

#ifndef CONFIGURATIONPARSER_HPP_
#define CONFIGURATIONPARSER_HPP_

#include <libconfig.h++>
#include "../Scene.hpp"
#include "../plugins/PluginsManager.hpp"

namespace raytracer::configuration_parser {
    class ConfigurationParser {
    public:
        explicit ConfigurationParser(const plugins::PluginsManager &pluginsManager);
        ~ConfigurationParser() = default;
        Scene parse(const std::string &filePath);
        [[nodiscard]] utils::AnyMap settingToMap(const libconfig::Setting &setting) const;

        static std::any parseValue(const libconfig::Setting &setting);
    private:
        const plugins::PluginsManager &_pluginsManager;
        void setCamera(const libconfig::Setting &camera, SceneBuilder &sceneBuilder) const;
    };
}

#endif /* !CONFIGURATIONPARSER_HPP_ */
