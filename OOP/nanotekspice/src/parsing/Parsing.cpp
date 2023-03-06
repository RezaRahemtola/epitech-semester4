/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Parsing.cpp
*/

#include <regex>
#include "NTS.hpp"
#include "Parsing.hpp"

static std::pair<std::string, std::size_t> getComponentNameAndPin(const std::string &serializedLink)
{
    const std::regex linkRegex("([a-zA-Z0-9_]+):(\\d+)");
    std::smatch match;
    std::regex_match(serializedLink, match, linkRegex);

    if (match.size() != 3)
        throw nts::Error("Parser: Invalid link format.");
    return std::make_pair(match[1], std::stoi(match[2]));
}

nts::Parser::Parser(nts::component::Circuit &circuit) : circuit(circuit)
{
}

bool nts::Parser::getNextLine()
{
    std::string tmp;

    while (tmp.empty()) {
        if (this->stream.eof())
            return false;
        if (!this->stream.good())
            throw nts::Error("Parser: Stream error.");
        getline(stream, tmp);

        std::stringstream ss(tmp);
        getline(ss, tmp, '#');

        this->line = std::stringstream(tmp);
    }
    return true;
}

std::string nts::Parser::getLineArgument()
{
    std::string arg;

    this->line >> arg;
    if (arg.empty())
        throw nts::Error("Parser: Incomplete line (missing argument).");
    return arg;
}

nts::Parser::Section nts::Parser::getLineSectionType()
{
    std::string savedLine(this->line.str());
    std::string arg;
    nts::Parser::Section lineSection = NONE;

    this->line >> arg;
    if (arg == ".chipsets:")
        lineSection = CHIPSETS;
    if (arg == ".links:")
        lineSection = LINKS;

    this->line = std::stringstream(savedLine);
    return lineSection;
}

bool nts::Parser::setAndCheckSection()
{
    Section lineSection = this->getLineSectionType();
    Section currentSection = this->section;

    if (lineSection != NONE)
        this->section = lineSection;
    if ((currentSection == NONE && lineSection != CHIPSETS) || (currentSection == lineSection))
        return false;
    return true;
}

void nts::Parser::createCircuitFromFile(const std::string &filepath)
{
    this->stream = std::ifstream(filepath);
    bool hasChipset = false;

    while (this->getNextLine()) {
        if (!this->setAndCheckSection())
            throw nts::Error("Parser: Missing or invalid sections.");
        if (this->getLineSectionType() != NONE)
            continue;
        if (this->section == CHIPSETS) {
            std::string type = this->getLineArgument();
            std::string name = this->getLineArgument();

            if (type == "nor" || type == "nand")
                throw nts::Error("Parser: Internal type can't be created from config file.");
            this->circuit.createComponent(type, name);
            hasChipset = true;
        } else if (this->section == LINKS) {
            if (!hasChipset)
                throw nts::Error("Parser: No chipset found.");
            std::pair source = getComponentNameAndPin(this->getLineArgument());
            std::pair destination = getComponentNameAndPin(this->getLineArgument());
            if (!this->circuit.containsComponent(source.first) || !this->circuit.containsComponent(destination.first))
                throw nts::Error("Parser: Invalid link (unknown component(s)).");
            auto &sourceComponent = this->circuit[source.first];
            auto &destinationComponent = this->circuit[destination.first];
            component::Link effectiveLinkToSource = sourceComponent.getEffectiveLink(source.second);
            component::Link effectiveLinkToDestination = destinationComponent.getEffectiveLink(destination.second);

            effectiveLinkToSource.component.setLink(effectiveLinkToSource.pin, effectiveLinkToDestination);
            effectiveLinkToDestination.component.setLink(effectiveLinkToDestination.pin, effectiveLinkToSource);
        }
    }
    if (this->section != LINKS)
        throw nts::Error("Parser: Missing section(s).");
}
