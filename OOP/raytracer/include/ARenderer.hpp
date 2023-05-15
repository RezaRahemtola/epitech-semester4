/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-raytracer-reza.rahemtola
** File description:
** ARender
*/

#ifndef ARENDERER_HPP_
#define ARENDERER_HPP_

#include <memory>
#include <vector>

#include "AShape.hpp"

namespace raytracer {
    class Scene;

    namespace render {
        class ARenderer {
        public:
            virtual ~ARenderer() = default;

            [[nodiscard]] virtual std::vector<utils::Color> render(const Scene &scene) const = 0;
        };
    }
}

#endif /* !ARENDERER_HPP_ */
