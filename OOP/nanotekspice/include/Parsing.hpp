/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Parsing
*/

#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include "components/circuits/Circuit.hpp"

namespace nts {
    class Parser {
        public:
            explicit Parser(nts::component::Circuit &circuit);
            void createCircuitFromFile(const std::string &filepath);

            enum Section {
                NONE,
                CHIPSETS,
                LINKS
            };

        private:
            bool getNextLine();
            std::string getLineArgument();

            bool setAndCheckSection();
            Section getLineSectionType();

            std::ifstream stream;
            std::stringstream line;
            Section section = NONE;
            nts::component::Circuit &circuit;
    };
}
