/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** SFMLOutputGenerator
*/

#include "SFMLOutputGenerator.hpp"

namespace raytracer::output {
    SFMLOutputGenerator::SFMLOutputGenerator(const plugins::Arguments &)
    {}

    void SFMLOutputGenerator::makeOutput(std::vector<utils::Color> pixels, size_t height, size_t width) const
    {
        sf::RenderWindow window(sf::VideoMode(width, height), "SFML");
        sf::Event event{};

        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            for (size_t y = 0; y < height; ++y)
                for (size_t x = 0; x < width; ++x) {
                    sf::RectangleShape rectShape(sf::Vector2f(1, 1));
                    rectShape.setPosition(
                            static_cast<float>(x),
                            static_cast<float>(y)
                    );
                    rectShape.setFillColor(
                            sf::Color(
                                    pixels[y * width + x].x,
                                    pixels[y * width + x].y,
                                    pixels[y * width + x].z
                            )
                    );
                    window.draw(rectShape);
                }
            window.display();
        }
    }
}
