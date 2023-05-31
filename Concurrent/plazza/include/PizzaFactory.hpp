/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** PizzaFactory.hpp
*/

#ifndef PIZZAFACTORY_HPP_
#define PIZZAFACTORY_HPP_

#include <memory>
#include <unordered_map>
#include "Pizza.hpp"

namespace plazza::reception {
    class PizzaFactory {
    public:
        explicit PizzaFactory()
        {
            registerPizza<ReginaPizza>("regina");
            registerPizza<MargaritaPizza>("margarita");
            registerPizza<AmericanaPizza>("americana");
            registerPizza<FantasiaPizza>("fantasia");
            registerPizza<DelamamaPizza>("delamama");
        }

        std::unique_ptr<IPizza> createPizza(const std::string &pizzaName, const PizzaSize size) const
        {
            auto pizzaCreatorIt = _pizzaFactory.find(pizzaName);

            if (pizzaCreatorIt == _pizzaFactory.end())
                throw std::runtime_error("Unknown pizza name: " + pizzaName);

            return (this->*(pizzaCreatorIt->second))(size);
        }

        template<typename TPizza, typename = typename std::enable_if<std::is_base_of<plazza::IPizza, TPizza>::value>::type>
        std::unique_ptr<IPizza> createGenericPizza(const PizzaSize size) const
        {
            return std::make_unique<TPizza>(size);
        }

        template<typename TPizza, typename = typename std::enable_if<std::is_base_of<plazza::IPizza, TPizza>::value>::type>
        void registerPizza(const std::string &pizzaName)
        {
            _pizzaFactory[pizzaName] = &PizzaFactory::createGenericPizza<TPizza>;
        }

    private:
        using PizzaCreator = std::unique_ptr<IPizza> (PizzaFactory::*)(const PizzaSize) const;
        std::unordered_map<std::string, PizzaCreator> _pizzaFactory;
    };
}

#endif //PIZZAFACTORY_HPP_
