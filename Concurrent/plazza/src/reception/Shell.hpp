/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** Shell.hpp
*/

#ifndef SHELL_HPP_
#define SHELL_HPP_

#include <stdexcept>
#include <memory>
#include <regex>
#include "commands/ShellCommand.hpp"
#include "PizzaFactory.hpp"

namespace plazza::reception::ordering {
    class Shell {
    public:
        Shell();

        void start();
        void stop();
    private:
        bool _running = false;
        std::vector<std::unique_ptr<commands::ShellCommand>> _commands;
        reception::PizzaFactory _pizzaFactory;

        static const std::string NEWLINE;

        [[nodiscard]] bool parseAndExecuteCommand(std::string &input) noexcept;

        template<typename TCommand, typename = typename std::enable_if<std::is_base_of_v<class commands::ShellCommand,
                TCommand>>>
        void registerCommand()
        {
            _commands.push_back(std::make_unique<TCommand>());
        }

        [[nodiscard]] static bool
        isAliasOfCommand(const std::string &input, const std::unique_ptr<commands::ShellCommand> &command);
        bool parseAndSendOrder(const std::string &input) const;
        void sendOrder(const std::string &pizzaName, plazza::PizzaSize pizzaSize, std::size_t orderSize) const noexcept;
    };
}

#endif //SHELL_HPP_
