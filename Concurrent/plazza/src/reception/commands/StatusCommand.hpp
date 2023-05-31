/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** StatusCommand.hpp
*/

#ifndef STATUSCOMMAND_HPP_
#define STATUSCOMMAND_HPP_

#include "../Shell.hpp"
#include "ShellCommand.hpp"

namespace plazza::reception::ordering::commands {
    class StatusCommand : public ShellCommand {
    public:
        StatusCommand();

        void execute(Shell &shell, const std::vector<std::string> &arguments) final;
    };
}

#endif //STATUSCOMMAND_HPP_
