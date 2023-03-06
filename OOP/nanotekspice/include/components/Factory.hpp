/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Factory.hpp
*/

#pragma once

#include <unordered_map>
#include "IComponent.hpp"

namespace nts::component {
    class Factory {
    public:
        Factory();

        std::unique_ptr<nts::component::IComponent>
        createComponent(const std::string &type);
    private:
        template<typename T>
        std::unique_ptr<IComponent> createGenericComponent()
        {
            return std::make_unique<T>();
        }

        std::unordered_map<std::string, std::unique_ptr<IComponent> (Factory::*)()> constructors;
    };
}
