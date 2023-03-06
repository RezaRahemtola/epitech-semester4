/*
** EPITECH PROJECT, 2023
** nts
** File description:
** Factory.cpp
*/

#include "NTS.hpp"
#include "components/Factory.hpp"
#include "components/gates/Gates.hpp"
#include "components/special/Special.hpp"
#include "components/circuits/Circuits.hpp"

nts::component::Factory::Factory()
{
    this->constructors["and"] = &Factory::createGenericComponent<And>;
    this->constructors["or"] = &Factory::createGenericComponent<Or>;
    this->constructors["not"] = &Factory::createGenericComponent<Not>;
    this->constructors["xor"] = &Factory::createGenericComponent<Xor>;
    this->constructors["nand"] = &Factory::createGenericComponent<Nand>;
    this->constructors["nor"] = &Factory::createGenericComponent<Nor>;
    this->constructors["input"] = &Factory::createGenericComponent<Input>;
    this->constructors["clock"] = &Factory::createGenericComponent<Clock>;
    this->constructors["output"] = &Factory::createGenericComponent<Output>;
    this->constructors["true"] = &Factory::createGenericComponent<TrueComponent>;
    this->constructors["false"] = &Factory::createGenericComponent<FalseComponent>;
    this->constructors["4001"] = &Factory::createGenericComponent<Circuit4001>;
    this->constructors["4011"] = &Factory::createGenericComponent<Circuit4011>;
    this->constructors["4030"] = &Factory::createGenericComponent<Circuit4030>;
    this->constructors["4069"] = &Factory::createGenericComponent<Circuit4069>;
    this->constructors["4071"] = &Factory::createGenericComponent<Circuit4071>;
    this->constructors["4081"] = &Factory::createGenericComponent<Circuit4081>;
}

std::unique_ptr<nts::component::IComponent> nts::component::Factory::createComponent(const std::string &type)
{
    if (this->constructors.find(type) == this->constructors.end())
        throw nts::Error("Factory: Unknown component type");
    return (this->*this->constructors[type])();
}
