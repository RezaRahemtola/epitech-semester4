/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** Fork
*/

#pragma once

#include <csignal>
#include <cstdlib>
#include <functional>

namespace plazza {
    class Fork {
        public:
            static void create(const std::function<void(void)> &func)
            {
                int pid = fork();

                if (pid == 0) {
                    // TODO: catch errors
                    func();
                    exit(0);
                } else if (pid == -1) {
                    // TODO: throw error
                }
            }
    };
}
