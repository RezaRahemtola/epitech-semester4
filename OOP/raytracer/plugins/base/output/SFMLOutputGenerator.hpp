/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** sceneSfml
*/

#ifndef SFMLOUTPUTGENERATOR_HPP_
#define SFMLOUTPUTGENERATOR_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "AOutputGenerator.hpp"
#include "Plugin.hpp"

namespace raytracer::output {
    class SFMLOutputGenerator : public AOutputGenerator {
    public:
        ~SFMLOutputGenerator() override = default;
        explicit SFMLOutputGenerator(const plugins::Arguments &);

        void makeOutput(std::vector<utils::Color> pixels, size_t height, size_t width) const override;
    };
}


#endif /* !SFMLOUTPUTGENERATOR_HPP_ */
