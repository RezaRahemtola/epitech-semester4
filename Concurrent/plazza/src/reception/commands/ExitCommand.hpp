/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** ExitCommand.hpp
*/

#ifndef EXITCOMMAND_HPP_
#define EXITCOMMAND_HPP_

#include "../Shell.hpp"
#include "ShellCommand.hpp"

namespace plazza::reception::ordering::commands {
    class ExitCommand : public ShellCommand {
    public:
        ExitCommand();
        void execute(Shell &shell, const std::vector<std::string> &arguments) override;
    };
}

#endif //EXITCOMMAND_HPP_
