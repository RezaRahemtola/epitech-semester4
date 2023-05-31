/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** CTPizza
*/

#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include "ISerializable.hpp"
#include "../src/Utils.hpp"

namespace plazza {
    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8,
        Delamama = 16
    };

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    enum PizzaIngredient {
        Dough = 0,
        Tomato = 1,
        Gruyere = 2,
        Ham = 3,
        Mushrooms = 4,
        Steak = 5,
        Eggplant = 6,
        GoatCheese = 7,
        ChiefLove = 8,
    };

    static std::unordered_map<std::string, PizzaSize> pizzaSizeMappings = {
            {"S",   S},
            {"M",   M},
            {"L",   L},
            {"XL",  XL},
            {"XXL", XXL}
    };

    static std::unordered_map<PizzaType, std::string> pizzaNameMappings = {
            {Regina,    "Regina"},
            {Margarita, "Margarita"},
            {Americana, "Americana"},
            {Fantasia,  "Fantasia"},
            {Delamama,  "Delamama"}
    };


    class IPizza {
    public:
        virtual ~IPizza() = default;
        [[nodiscard]] virtual std::vector<PizzaIngredient> getIngredients() const noexcept = 0;
        [[nodiscard]] virtual PizzaType getType() const noexcept = 0;
        [[nodiscard]] virtual PizzaSize getSize() const noexcept = 0;
        [[nodiscard]] virtual size_t getBakingTime() const noexcept = 0;
        [[nodiscard]] virtual std::string getName() const noexcept = 0;
    };

    class Pizza : public IPizza, public utils::ISerializable {
    public:
        explicit Pizza(const PizzaSize size, const PizzaType pizzaType, const std::size_t bakingTime,
                       const std::vector<PizzaIngredient> &ingredients)
                : _size(size), _ingredients(ingredients), _pizzaType(pizzaType), _bakingTime(bakingTime)
        {};

        [[nodiscard]] std::vector<PizzaIngredient> getIngredients() const noexcept override
        {
            return _ingredients;
        }

        [[nodiscard]] PizzaType getType() const noexcept override
        {
            return _pizzaType;
        }

        [[nodiscard]] PizzaSize getSize() const noexcept override
        {
            return _size;
        }

        [[nodiscard]] size_t getBakingTime() const noexcept override
        {
            return _bakingTime;
        }

        [[nodiscard]] std::string getName() const noexcept override
        {
            return pizzaNameMappings[_pizzaType];
        }

        [[nodiscard]] std::string pack() const override
        {
            std::string packedPizza = std::to_string(_pizzaType) + ";" + std::to_string(_size) + ";" +
                                      std::to_string(_bakingTime);
            for (const auto &ingredient: _ingredients)
                packedPizza += ";" + std::to_string(ingredient);
            return packedPizza;
        }

        [[nodiscard]] static Pizza unpack(const std::string &packedPizza)
        {
            std::vector<std::string> tokens = utils::split(packedPizza, std::regex(";"));
            auto pizzaType = static_cast<PizzaType>(std::stoi(tokens[0]));
            auto pizzaSize = static_cast<PizzaSize>(std::stoi(tokens[1]));
            size_t bakingTime = std::stoi(tokens[2]);
            std::vector<PizzaIngredient> ingredients;
            for (size_t i = 3; i < tokens.size(); i++)
                ingredients.push_back(static_cast<PizzaIngredient>(std::stoi(tokens[i])));
            return Pizza(pizzaSize, pizzaType, bakingTime, ingredients);
        }

    private:
        const PizzaSize _size;
        const std::vector<PizzaIngredient> _ingredients;
        const PizzaType _pizzaType;
        const size_t _bakingTime;
    };

    template<PizzaType pizzaType, std::size_t bakingTime, PizzaIngredient... ingredients>
    class CTPizza : public Pizza {
    public:
        explicit CTPizza(const PizzaSize &size) : Pizza(size, pizzaType, bakingTime, {ingredients...})
        {};
    };

    using MargaritaPizza = CTPizza<Margarita, 1, Dough, Tomato, Gruyere>;
    using ReginaPizza = CTPizza<Regina, 2, Dough, Tomato, Gruyere, Ham, Mushrooms>;
    using AmericanaPizza = CTPizza<Americana, 2, Dough, Tomato, Gruyere, Steak>;
    using FantasiaPizza = CTPizza<Fantasia, 4, Dough, Tomato, Eggplant, GoatCheese, ChiefLove>;
    using DelamamaPizza = CTPizza<Delamama, 1, Dough, Tomato, ChiefLove>;
}
