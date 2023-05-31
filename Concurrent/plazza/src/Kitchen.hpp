/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** Kitchen
*/

#pragma once

#include <unordered_map>
#include <chrono>
#include "Pizza.hpp"
#include "ThreadPool.hpp"
#include "MessageQueue.hpp"

namespace plazza {
    class Kitchen {
        public:
            explicit Kitchen(std::size_t id, std::size_t nbCooks, std::size_t stockRegenerationInterval, double
            cookingTimeMultiplier);

            void start();
        private:
            static constexpr std::size_t INITIAL_INGREDIENT_STOCK = 5;
            static constexpr std::size_t INGREDIENT_REGENERATION = 1;
            static constexpr std::size_t MAX_IDLE_DURATION = 5;

            std::size_t _id;
            std::size_t _nbCooks;
            std::size_t _stockRegenerationInterval;
            double _cookingTimeMultiplier;
            std::chrono::time_point<std::chrono::system_clock> _lastStockRegeneration;
            std::chrono::time_point<std::chrono::system_clock> _idleTimer;
            std::unordered_map<PizzaIngredient, std::size_t> _ingredientStock;
            std::unique_ptr<utils::MessageQueue> _queue;

            void regenerateStock() noexcept;
            bool useIngredients(const std::vector<PizzaIngredient> &ingredients) noexcept;
            bool shouldClose(const ThreadPool &pool);
    };
}
