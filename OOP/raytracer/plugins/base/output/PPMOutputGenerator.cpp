/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PPMOutputGenerator
*/

#include "PPMOutputGenerator.hpp"
#include "Plugin.hpp"

namespace raytracer::output {
    void PPMOutputGenerator::makeOutput(std::vector<utils::Color> pixels, size_t height, size_t width) const
    {
        std::ofstream ppmFile("scene.ppm");

        if (!ppmFile.is_open()) {
            std::cerr << "Failed to open PPM file" << std::endl;
            return;
        }
        ppmFile << "P3\n" << width << " " << height << "\n255\n";
        for (size_t y = 0; y < height; y++) {
            for (size_t x = 0; x < width; x++) {
                ppmFile << pixels[y * width + x].x << " " << pixels[y * width + x].y << " "
                        << pixels[y * width + x].z << " ";
            }
            ppmFile << "\n";
        }
        ppmFile.close();
    }

    PPMOutputGenerator::PPMOutputGenerator(const plugins::Arguments &)
    {}
}
