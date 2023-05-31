/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** ISerializable.hpp
*/

#ifndef ISERIALIZABLE_HPP_
#define ISERIALIZABLE_HPP_

namespace plazza::utils {
    class ISerializable {
    public:
        virtual ~ISerializable() = default;
        [[nodiscard]] virtual std::string pack() const = 0;
    };
}

#endif //ISERIALIZABLE_HPP_
