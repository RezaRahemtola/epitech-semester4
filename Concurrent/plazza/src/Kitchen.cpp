/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** Kitchen
*/

#include <iostream>
#include "Kitchen.hpp"
#include "Pizza.hpp"

plazza::Kitchen::Kitchen(std::size_t id, std::size_t nbCooks, std::size_t stockRegenerationInterval, double
cookingTimeMultiplier) :
        _id(id),
        _nbCooks(nbCooks), _stockRegenerationInterval(stockRegenerationInterval),
        _cookingTimeMultiplier(cookingTimeMultiplier)
{
    _ingredientStock = {{Dough,      INITIAL_INGREDIENT_STOCK},
                        {Tomato,     INITIAL_INGREDIENT_STOCK},
                        {Gruyere,    INITIAL_INGREDIENT_STOCK},
                        {Ham,        INITIAL_INGREDIENT_STOCK},
                        {Mushrooms,  INITIAL_INGREDIENT_STOCK},
                        {Steak,      INITIAL_INGREDIENT_STOCK},
                        {Eggplant,   INITIAL_INGREDIENT_STOCK},
                        {GoatCheese, INITIAL_INGREDIENT_STOCK},
                        {ChiefLove,  INITIAL_INGREDIENT_STOCK}};
    _lastStockRegeneration = std::chrono::system_clock::now();
    _idleTimer = std::chrono::system_clock::now();
    _queue = std::make_unique<plazza::utils::MessageQueue>("/plazza-kitchen-" + std::to_string(id), nbCooks);
}

void plazza::Kitchen::regenerateStock() noexcept
{
    if ((std::chrono::system_clock::now() - _lastStockRegeneration) >=
        std::chrono::milliseconds(_stockRegenerationInterval)) {
        for (const auto &[key, value]: _ingredientStock) {
            _ingredientStock[key] += INGREDIENT_REGENERATION;
        }
        _lastStockRegeneration = std::chrono::system_clock::now();
    }
}

bool plazza::Kitchen::useIngredients(const std::vector<PizzaIngredient> &ingredients) noexcept
{
    for (const auto &ingredient: ingredients) {
        if (_ingredientStock[ingredient] == 0)
            return (false);
    }
    for (const auto &ingredient: ingredients)
        _ingredientStock[ingredient]--;
    return (true);
}

bool plazza::Kitchen::shouldClose(const ThreadPool &pool)
{
    if ((std::chrono::system_clock::now() - _idleTimer) >=
        std::chrono::seconds(MAX_IDLE_DURATION)) {
        return true;
    }
    if (!pool.allFree()) {
        _idleTimer = std::chrono::system_clock::now();
    }
    return false;
}

void plazza::Kitchen::start()
{
    std::cout << "Kitchen " << _id << " open" << std::endl;
    ThreadPool cooks(_nbCooks);

    while (!this->shouldClose(cooks)) {
        this->regenerateStock();

        auto data = _queue->receive();
        if (!data.has_value())
            continue;
        auto packed = std::move(*data);
        auto pizza = Pizza::unpack(packed);

        if (!this->useIngredients(pizza.getIngredients())) {
            return;
        }
        cooks.addTask([this, pizza] {
            auto delay = static_cast<int>(pizza.getBakingTime() * 1000 * _cookingTimeMultiplier);
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            std::cout << "[Kitchen " << _id << "] Done cooking " << pizza.getName() << std::endl;

        });
    }
    // TODO: signal close to the reception
}
