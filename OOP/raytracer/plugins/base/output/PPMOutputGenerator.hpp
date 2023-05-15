/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PPMOutputGenerator
*/

#ifndef PPMOUTPUTGENERATOR_HPP_
#define PPMOUTPUTGENERATOR_HPP_

#include <iostream>
#include <fstream>
#include <unordered_map>

#include "AOutputGenerator.hpp"
#include "Plugin.hpp"

namespace raytracer::output {
    class PPMOutputGenerator : public AOutputGenerator {
    public:
        explicit PPMOutputGenerator(const plugins::Arguments &);
        ~PPMOutputGenerator() override = default;

        void makeOutput(std::vector<utils::Color> pixels, size_t height, size_t width) const override;
    };
}

#endif /* !PPMOUTPUTGENERATOR_HPP_ */
