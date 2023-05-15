/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Base
*/

#pragma once

#include "APlugin.hpp"

namespace raytracer::plugins {
    class Plugin : public APlugin {
        public:
            Plugin();
    };

    extern "C" Plugin *raytracerPluginEntrypoint();
}
