/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** Reception.hpp
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "../configuration/Configuration.hpp"
#include "Shell.hpp"

namespace plazza::reception {
    class Reception {
    public:
        explicit Reception(const configuration::Configuration &configuration);

        void open();
    private:
        bool _open = false;
        const configuration::Configuration &_configuration;
        ordering::Shell _shell;
    };
}

#endif //RECEPTION_HPP_
