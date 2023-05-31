/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** ExitCommand.cpp
*/

#include "ExitCommand.hpp"

void plazza::reception::ordering::commands::ExitCommand::execute(
        Shell &shell, const std::vector<std::string> &arguments)
{
    shell.stop();
}

plazza::reception::ordering::commands::ExitCommand::ExitCommand() : ShellCommand("exit", {"aurevoir", "goodbye",
                                                                                          "arrivederci"})
{}
