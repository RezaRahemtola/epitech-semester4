/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Circuit
*/

#include <utility>
#include "NTS.hpp"
#include "components/Factory.hpp"
#include "components/circuits/Circuit.hpp"
#include "components/special/Input.hpp"
#include "components/special/Output.hpp"

void nts::component::Circuit::simulate(std::size_t tick)
{
    // TODO
    this->currentTick = tick;
}

nts::component::Tristate nts::component::Circuit::compute(std::size_t pin, std::size_t tick)
{
    // TODO: useless ?
    if (!this->internalLinks.contains(pin)) return Undefined; // TODO: throw error ?
    auto link = this->internalLinks.at(pin);
    this->pins[pin] = link.component.compute(link.pin, tick);
    return this->pins[pin];
}

void nts::component::Circuit::createComponent(const std::string &type, const std::string &name)
{
    Factory factory;

    if (this->components.contains(name))
        throw nts::Error("Circuit: component creation failed: duplicated name");
    this->components[name] = factory.createComponent(type);

    auto input = dynamic_cast<nts::component::Input *>(this->components[name].get());
    if (input != nullptr)
        this->inputNames.push_back(name);

    auto output = dynamic_cast<nts::component::Output *>(this->components[name].get());
    if (output != nullptr)
        this->outputNames.push_back(name);
}

void nts::component::Circuit::setInputValue(const std::string &name, nts::component::Tristate state)
{
    // TODO: we could use the inputNames, but still need to do a cast
    if (!this->components.contains(name))
        return;

    auto component = dynamic_cast<nts::component::Input *>(this->components[name].get());
    if (component == nullptr)
        return;
    component->setNewState(state);
}

void nts::component::Circuit::display()
{
    this->displayIO<Input>(this->inputNames, "input(s):");
    this->displayIO<Output>(this->outputNames, "output(s):");
}

nts::component::IComponent &nts::component::Circuit::operator[](const std::string &name)
{
    return *this->components[name];
}

bool nts::component::Circuit::containsComponent(const std::string &name)
{
    return this->components.contains(name);
}

nts::component::Link nts::component::Circuit::getEffectiveLink(std::size_t pin)
{
    if (!this->pins.contains(pin))
        throw nts::Error("Circuit: pin not found");
    if (!this->internalLinks.contains(pin))
        throw nts::Error("Circuit: pin is not used");
    auto &[internalComponentPin, internalComponent] = this->internalLinks.at(pin);

    return internalComponent.getEffectiveLink(internalComponentPin);
}

void nts::component::Circuit::createInternalLink(std::size_t hostPin, nts::component::Link internalLink)
{
    this->internalLinks.insert({hostPin, internalLink});
}

std::vector<std::string> nts::component::Circuit::getInputNames() const
{
    return this->inputNames;
}

std::vector<std::string> nts::component::Circuit::getOutputNames() const
{
    return this->outputNames;
}

void nts::component::Circuit::initializePins(const std::vector<std::size_t> &pinsToInitialize)
{
    for (const auto &pin: pinsToInitialize)
        this->pins.insert({pin, Undefined});
}
