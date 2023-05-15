cmake_minimum_required(VERSION 3.10)

project(raytracer)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_compile_options(-Wall -Wextra -Wpedantic -g3)
else ()
    add_compile_options(-O3)
endif ()

add_executable(raytracer
    src/main.cpp
    include/AShape.hpp
    include/Ray.hpp
    include/ALight.hpp
    include/APositionedLight.hpp
    include/ARenderer.hpp
    include/AOutputGenerator.hpp
    include/APlugin.hpp
    include/Plugin.hpp
    src/camera/Camera.hpp
    src/camera/Camera.cpp
    src/plugins/PluginsManager.cpp src/plugins/PluginsManager.hpp
    src/configuration/ConfigurationParser.cpp src/configuration/ConfigurationParser.hpp
    src/Scene.cpp src/Scene.hpp)

target_include_directories(raytracer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(raytracer PRIVATE sfml-graphics sfml-window sfml-system config++ dl)
target_compile_features(raytracer PRIVATE cxx_std_20)

include(plugins/base/base-plugin.cmake)
