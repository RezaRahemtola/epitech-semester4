/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Circuit
*/

#pragma once

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include "../AComponent.hpp"

namespace nts::component {
    class Circuit : public AComponent {
    public:
        void simulate(std::size_t tick) override;
        Tristate compute(std::size_t pin, std::size_t tick) override;
        Link getEffectiveLink(std::size_t pin) override;

        void createComponent(const std::string &type, const std::string &name);
        void setInputValue(const std::string &name, Tristate state);
        bool containsComponent(const std::string &name);

        IComponent &operator[](const std::string &name);

        std::vector<std::string> getInputNames() const;
        std::vector<std::string> getOutputNames() const;
        void display();
    protected:
        void createInternalLink(std::size_t hostPin, Link internalLink);
        void initializePins(const std::vector<std::size_t> &pinsToInitialize);
    private:
        template<typename T>
        void displayIO(std::vector<std::string> names, const std::string &text)
        {
            std::cout << text << std::endl;

            std::sort(names.begin(), names.end());
            for (const auto &name: names) {
                auto component = dynamic_cast<T *>(this->components[name].get());
                if (component == nullptr)
                    continue;

                Tristate state = component->getPinSate(1);
                char stateChar = (state == Tristate::Undefined) ? 'U' : (state == Tristate::True) ? '1' : '0';
                std::cout << "  " << name << ": " << stateChar << std::endl;
            }
        };

        std::vector<std::string> inputNames;
        std::vector<std::string> outputNames;
        std::unordered_map<std::string, std::unique_ptr<IComponent>> components;
        std::unordered_map<std::size_t, Link> internalLinks;
    };
}
