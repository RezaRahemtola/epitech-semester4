/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** Shell.cpp
*/

#include <thread>
#include <iostream>
#include "Shell.hpp"
#include "commands/StatusCommand.hpp"
#include "commands/ExitCommand.hpp"
#include "PizzaFactory.hpp"
#include "../Utils.hpp"

namespace plazza::reception::ordering {

    void Shell::stop()
    {
        _running = false;
    }

    void Shell::start()
    {
        if (_running)
            throw std::runtime_error("Cannot start an already running ordering.");
        _running = true;
        std::string input;
        std::cout << "Hello, may I take your order?" << std::endl;
        while (_running) {
            std::getline(std::cin, input);
            if (std::cin.eof())
                this->stop();
            else if (!this->parseAndExecuteCommand(input) && !this->parseAndSendOrder(input))
                std::cerr << "This input is not a valid command nor a valid order." << std::endl;
        }
        std::cout << "Thank you for coming, hope to see you again, goodbye!" << std::endl;
    }

    bool Shell::parseAndExecuteCommand(std::string &input) noexcept
    {
        auto arguments = utils::split(input, std::regex("\\s+Z"));
        if (arguments.empty())
            return false;
        auto commandLabel = arguments.front();
        arguments.erase(arguments.begin());

        const auto &command = std::find_if(
                _commands.begin(), _commands.end(),
                [&commandLabel](const auto &command) {
                    return Shell::isAliasOfCommand(commandLabel, command);
                }
        );

        if (command == _commands.end())
            return false;

        command->get()->execute(*this, arguments);
        return true;
    }

    bool Shell::parseAndSendOrder(const std::string &input) const
    {
        std::vector<std::string> orders = utils::split(input, std::regex("\\s*;\\s*"));

        if (orders.empty())
            return false;
        for (const auto &order: orders) {
            std::regex regex(R"(^\s*([a-zA-Z]+)\s+(S|M|L|XL|XXL)\s+x([1-9]\d*)\s*$)");
            std::smatch match;

            if (!std::regex_match(order, match, regex))
                return false;
            auto orderSize = std::stoi(match[3].str());

            if (orderSize <= 0 || !plazza::pizzaSizeMappings.contains(match[2].str()))
                return false;
            Shell::sendOrder(match[1].str(), plazza::pizzaSizeMappings[match[2].str()], orderSize);
        }
        std::cout << "Your order has been sent." << std::endl;
        return true;
    }

    bool Shell::isAliasOfCommand(const std::string &input, const std::unique_ptr<commands::ShellCommand> &command)
    {
        return input == command->getLabel()
               || std::find(command->getAliases().begin(), command->getAliases().end(), input)
                  != command->getAliases().end();
    }

    Shell::Shell()
    {
        this->registerCommand<commands::StatusCommand>();
        this->registerCommand<commands::ExitCommand>();
    }

    void Shell::sendOrder(
            const std::string &pizzaName, const plazza::PizzaSize pizzaSize, const std::size_t orderSize) const noexcept
    {
        std::vector<std::unique_ptr<IPizza>> pizzas(orderSize);

        std::generate(pizzas.begin(), pizzas.end(), [this, &pizzaName, &pizzaSize] {
            return _pizzaFactory.createPizza(pizzaName, pizzaSize);
        });

        // TODO: implement sending orders to kitchen via mq
    }
}
