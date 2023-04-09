/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** AGameModule
*/

#include "AGameModule.hpp"

namespace arcade {
    AGameModule::AGameModule() : score(0), gameOver(false), soundEffect()
    {
    }

    void AGameModule::scoreUp()
    {
        this->score += 50;
    }

    void AGameModule::setSound(common::Sound music)
    {
        this->soundEffect.push_back(music);
    }

    void AGameModule::setPlayer(arcade::common::Sprite body)
    {
        this->player.push_back(body);
    }

    void AGameModule::isGameOver()
    {
        this->gameOver = true;
    }
}
