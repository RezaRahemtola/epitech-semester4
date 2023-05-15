/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** AOutputGenerator
*/

#ifndef AOUTPUTGENERATOR_HPP_
#define AOUTPUTGENERATOR_HPP_

#include <vector>
#include <iostream>
#include "Utils.hpp"

namespace raytracer::output {
    class AOutputGenerator {
    public:
        virtual ~AOutputGenerator() = default;

        virtual void makeOutput(std::vector<utils::Color> pixels, size_t height, size_t width) const = 0;
    };
}

#endif /* !AOUTPUTGENERATOR_HPP_ */
