/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Parsing
*/

#include <algorithm>
#include <filesystem>
#include "Arcade.hpp"
#include "Core.hpp"

static std::vector<std::string> GRAPHICAL_LIBS = {
        "arcade_ncurses.so",
        "arcade_sdl2.so",
        "arcade_ndk++.so",
        "arcade_aalib.so",
        "arcade_libcaca.so",
        "arcade_allegro5.so",
        "arcade_xlib.so",
        "arcade_gtk+.so",
        "arcade_sfml.so",
        "arcade_irrlicht.so",
        "arcade_opengl.so",
        "arcade_vulkan.so",
        "arcade_qt5.so"
};

static std::vector<std::string> GAME_LIBS = {
        "arcade_snake.so",
        "arcade_nibbler.so",
        "arcade_pacman.so",
        "arcade_qix.so",
        "arcade_centipede.so",
        "arcade_solarfox.so",
};

void arcade::Core::parse(const std::string &initialLib)
{
    std::string library = std::filesystem::path(initialLib).filename();

    for (const auto &entry: std::filesystem::directory_iterator("./lib")) {
        std::string lib = entry.path().filename();

        if (std::find(GRAPHICAL_LIBS.begin(), GRAPHICAL_LIBS.end(), lib) != GRAPHICAL_LIBS.end()) {
            this->availableDisplays.push_back("./lib/" + lib);
        } else if (std::find(GAME_LIBS.begin(), GAME_LIBS.end(), lib) != GAME_LIBS.end()) {
            this->availableGames.push_back("./lib/" + lib);
        }
    }

    auto foundInitial = std::find(this->availableDisplays.begin(), this->availableDisplays.end(), "./lib/" + library);
    if (foundInitial == std::end(this->availableDisplays))
        throw arcade::Error("Invalid libraries: '" + library + "' wasn't found in available graphical libraries.");
    if (this->availableGames.empty())
        throw arcade::Error("Invalid libraries: At least one game library must be available.");
    this->displayIndex = foundInitial - this->availableDisplays.begin();
    this->gameIndex = 0;
}
