/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** StatusCommand.cpp
*/

#include <iostream>
#include "StatusCommand.hpp"

plazza::reception::ordering::commands::StatusCommand::StatusCommand() : ShellCommand("status")
{}

void plazza::reception::ordering::commands::StatusCommand::execute(Shell &shell,
                                                                   const std::vector<std::string> &arguments)
{
    std::cout << "Hello from status" << std::endl;
}
