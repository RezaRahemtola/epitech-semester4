/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** Configuration.cpp
*/

#include <iostream>
#include <stdexcept>
#include "Configuration.hpp"

namespace plazza::configuration {
    Configuration::Configuration(const std::vector<std::string> &arguments)
    {
        if (arguments.size() != 4)
            throw InvalidArgumentException("Invalid number of arguments");
        this->parse(arguments);
    }

    const std::string &Configuration::getPath() const
    {
        return _path;
    }

    double Configuration::getCookingTimeMultiplier() const
    {
        return _cookingTimeMultiplier;
    }

    int Configuration::getCooksNumber() const
    {
        return _cooksNumber;
    }

    int Configuration::getRefillTime() const
    {
        return _refillTime;
    }

    void Configuration::parse(const std::vector<std::string> &arguments)
    {
        _path = arguments[0];
        try {
            _cookingTimeMultiplier = std::stod(arguments[1]);
            _cooksNumber = std::stoi(arguments[2]);
            _refillTime = std::stoi(arguments[3]);

            if (_cookingTimeMultiplier <= 0 || _cooksNumber <= 0 || _refillTime <= 0)
                throw std::out_of_range("");
        } catch (std::invalid_argument &) {
            throw InvalidArgumentException("An argument couldn't be converted to a number");
        } catch (std::out_of_range &) {
            throw InvalidArgumentException("An argument is out of range");
        }
    }

    void Configuration::showHelp(const std::string &binary) noexcept
    {
        std::cerr << "USAGE: " << binary << " <cooking time multiplier> <number of cooks> <ingredients refill time>"
                  << std::endl << std::endl;
        std::cerr << "DESCRIPTION:" << std::endl;
        std::cerr << "\tcooking time multiplier\t: positive floating point number representing the number by which" <<
                  std::endl << "\t\t\t\t" << "the cooking time of a pizza is multiplied." << std::endl;
        std::cerr << "\tnumber of cooks\t\t: positive integer representing the number of cooks in each kitchen." <<
                  std::endl;
        std::cerr << "\tingredients refill time\t: positive integer representing the time in milliseconds used by" <<
                  std::endl << "\t\t\t\t" << "the kitchen stock to refill 1 ingredient." << std::endl;
    }
}
