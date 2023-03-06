/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Simulator
*/

#pragma once

#include <unordered_map>
#include "components/circuits/Circuit.hpp"

namespace nts {
    class Simulator {
        public:
            explicit Simulator(nts::component::Circuit &circuit);
            void run();
        private:
            bool getUserInput();
            void changeInputComponent();

            void exit();
            void display();
            void simulate();
            void loop();

            std::unordered_map<std::string, void (Simulator::*)()> commands;
            std::string input;
            size_t currentTick = 0;
            nts::component::Circuit &circuit;
    };
}
