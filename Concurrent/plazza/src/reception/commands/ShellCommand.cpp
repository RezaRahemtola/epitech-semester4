/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** ShellCommand.cpp
*/

#include "ShellCommand.hpp"

#include <utility>

namespace plazza::reception::ordering::commands {
    ShellCommand::ShellCommand(std::string label, const std::vector<std::string> &aliases) noexcept
            : _label(std::move(label)), _aliases(aliases)
    {}

    const std::string &ShellCommand::getLabel() const
    {
        return _label;
    }

    const std::vector<std::string> &ShellCommand::getAliases() const
    {
        return _aliases;
    }
}
