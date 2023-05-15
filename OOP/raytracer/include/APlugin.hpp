/*
** EPITECH PROJECT, 2023
** Project
** File description:
** Plugins
*/

#pragma once

#include <memory>
#include "Plugin.hpp"
#include "ALight.hpp"
#include "AShape.hpp"
#include "ARenderer.hpp"
#include "AOutputGenerator.hpp"

namespace raytracer::plugins {
    template<typename ElementType>
    class PluginFactory {
    public:
        virtual ~PluginFactory() = default;

        std::unique_ptr<ElementType> createElement(const std::string &name, Arguments args)
        {
            if (_constructors.find(name) == _constructors.end())
                throw UnknownPluginComponentError("PluginFactory: Unknown element type");
            return (this->*_constructors[name])(args);
        }

        template<typename T, typename = typename std::enable_if<std::is_base_of<ElementType, T>::value>::type>
        void setElement(const std::string &name)
        {
            _constructors[name] = &PluginFactory::createGenericElement<T>;
        }

    protected:
        template<typename T, typename = typename std::enable_if<std::is_base_of<ElementType, T>::value>::type>
        std::unique_ptr<ElementType> createGenericElement(Arguments args)
        {
            return std::make_unique<T>(args);
        }

        std::unordered_map<std::string, std::unique_ptr<ElementType> (PluginFactory::*)(
                Arguments args)> _constructors;
    };

    class APlugin {
    public:
        virtual ~APlugin() = default;

        std::unique_ptr<lights::ILight>
        createLight(const std::string &name, const raytracer::plugins::Arguments &args)
        {
            return _lightFactory.createElement(name, args);
        }

        std::unique_ptr<shapes::IShape> createShape(const std::string &name, const Arguments &args)
        {
            return _shapeFactory.createElement(name, args);
        }

        std::unique_ptr<render::ARenderer> createRenderer(const std::string &name, const Arguments &args)
        {
            return _renderFactory.createElement(name, args);
        }

        std::unique_ptr<output::AOutputGenerator> createOutput(const std::string &name, const Arguments &args)
        {
            return _outputFactory.createElement(name, args);
        }


    protected:
        PluginFactory<lights::ILight> _lightFactory;
        PluginFactory<shapes::IShape> _shapeFactory;
        PluginFactory<render::ARenderer> _renderFactory;
        PluginFactory<output::AOutputGenerator> _outputFactory;
    };
}
