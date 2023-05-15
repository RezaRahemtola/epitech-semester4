/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** main.cpp
*/

#include "configuration/ConfigurationParser.hpp"

static bool parseAndLaunch(std::string const &configFile)
{
    raytracer::plugins::PluginsManager pluginsManager;
    pluginsManager.load();
    raytracer::configuration_parser::ConfigurationParser parser(pluginsManager);
    try {
        parser
                .parse(configFile)
                .render();
    } catch (libconfig::ParseException const &error) {
        std::cerr << "Parsing Error: " << error.getFile() << ":" << error.getLine()
                  << std::endl;
        return false;
    } catch (libconfig::SettingTypeException const &error) {
        std::cerr << "Invalid setting type: " << error.getPath() << std::endl;
        return false;
    } catch (libconfig::SettingNotFoundException const &error) {
        std::cerr << "Setting not found: " << error.getPath() << std::endl;
        return false;
    } catch (std::exception const &error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return false;
    }
    return true;
}

int main([[maybe_unused]] int argc, char *argv[])
{
    std::string configFile = "./configuration/config.cfg";

    if (argc > 3) {
        std::cerr << "Usage: " << argv[0] << " [configFile]" << std::endl;
        return 84;
    } else if (argc == 2)
        configFile = argv[1];


    if (!parseAndLaunch(configFile)) {
        std::cerr << "Failed to render the scene based on " << configFile << std::endl;
        return 84;
    }

    std::cout << "Finished render of the scene based on " << configFile << std::endl;
    return 0;
}
