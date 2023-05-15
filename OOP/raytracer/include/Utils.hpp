/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Utils.hpp
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <unordered_map>
#include <any>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <string>

namespace raytracer::utils {
    using Vector = sf::Vector3<double>;
    using Position = Vector;
    using Color = sf::Vector3i;
    using AnyMap = std::unordered_map<std::string, std::any>;

    constexpr double dotProduct(const Vector &a, const Vector &b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    constexpr double normOf(const utils::Vector &a)
    {
        return std::sqrt(dotProduct(a, a));
    }

    inline utils::Vector normalize(const utils::Vector &a)
    {
        return a / normOf(a);
    }

    template<typename T>
    sf::Vector3<T> mapToVector3(const AnyMap &map,
                                const std::tuple<std::string, std::string, std::string> &keys = {"x", "y", "z"})
    {
        const auto &[keyA, keyB, keyC] = keys;

        return sf::Vector3<T>(
                std::any_cast<T>(map.at(keyA)),
                std::any_cast<T>(map.at(keyB)),
                std::any_cast<T>(map.at(keyC))
        );
    }

    template<typename T>
    sf::Vector2<T> mapToVector2(const AnyMap &map, const std::tuple<std::string, std::string> &keys = {"x", "y"})
    {
        const auto &[keyA, keyB] = keys;

        return sf::Vector2<T>(
                std::any_cast<T>(map.at(keyA)),
                std::any_cast<T>(map.at(keyB))
        );
    }
}

#endif //UTILS_HPP_
