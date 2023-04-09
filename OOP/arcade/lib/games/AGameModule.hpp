/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** AGameModule
*/

#ifndef AGAME_HPP_
#define AGAME_HPP_

#include <string>
#include "../../include/common/game/IGameModule.hpp"
#include "../../include/common/Data.hpp"

namespace arcade {
    class AGameModule : public common::IGameModule {
        public:
            AGameModule();
            ~AGameModule() = default;
        protected:
            void isGameOver();

            void scoreUp();

            void setSound(common::Sound music);
            void setPlayer(arcade::common::Sprite body);

            unsigned int score;
            bool gameOver;
            std::vector<common::Sound> soundEffect;
            std::vector<arcade::common::Sprite> player;
    };
}

#endif /* !AGAME_HPP_ */
