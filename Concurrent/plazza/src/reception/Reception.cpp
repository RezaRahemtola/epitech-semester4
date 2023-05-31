/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** Reception.cpp
*/

#include <iostream>
#include <thread>
#include "Reception.hpp"

namespace plazza::reception {
    Reception::Reception(const configuration::Configuration &configuration) : _configuration(configuration)
    {}

    void Reception::open()
    {
        if (_open)
            throw std::runtime_error("The reception is already open");
        _open = true;
        std::cout << "The reception is opening..." << std::endl;
        std::thread shell(&ordering::Shell::start, &_shell);

        if (shell.joinable())
            shell.join();
    }
}
