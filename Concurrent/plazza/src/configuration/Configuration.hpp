/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** Configuration.hpp
*/

#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <utility>
#include <vector>
#include <string>

namespace plazza::configuration {
    class ConfigurationException : public std::exception {
    public:
        explicit ConfigurationException(const std::string &message)
                : _message(std::string("Configuration: ").append(message))
        {}

        [[nodiscard]] const char *what() const noexcept override
        {
            return _message.c_str();
        }

    private:
        std::string _message;
    };

    class InvalidArgumentException : public ConfigurationException {
    public:
        explicit InvalidArgumentException(const std::string &message)
                : ConfigurationException(std::string("Invalid argument: ").append(message))
        {}
    };

    class Configuration {
    public:
        explicit Configuration(const std::vector<std::string> &arguments);

        [[nodiscard]] const std::string &getPath() const;
        [[nodiscard]] double getCookingTimeMultiplier() const;
        [[nodiscard]] int getCooksNumber() const;
        [[nodiscard]] int getRefillTime() const;

        static void showHelp(const std::string &binary) noexcept;
    private:
        void parse(const std::vector<std::string> &arguments);

        std::string _path{};
        double _cookingTimeMultiplier{};
        int _cooksNumber{};
        int _refillTime{};
    };
}
#endif //CONFIGURATION_HPP_
