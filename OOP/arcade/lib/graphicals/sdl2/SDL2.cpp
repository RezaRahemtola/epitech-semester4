/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** SDL2
*/

#include "SDL2.hpp"

extern "C" arcade::SDL2 *displayEntrypoint()
{
    return new arcade::SDL2;
}

static const size_t WIDTH = 1920;
static const size_t HEIGHT = 1080;
static const size_t SIZE_X = 30;
static const size_t SIZE_Y = 25;

arcade::SDL2::SDL2()
{
    if (!SDL_Init(SDL_INIT_EVERYTHING)) {
        if (TTF_Init() < 0)
            std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
        this->_window = SDL_CreateWindow("Arcade - SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
                                         0);
        this->_rend = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
        this->_white = {255, 255, 255, 0};
        loadSprite();
    } else {
        std::cerr << SDL_GetError() << std::endl;
    }
}

arcade::SDL2::~SDL2()
{
    for (const auto &n: this->_texture) {
        SDL_DestroyTexture(n);
    }
    SDL_DestroyRenderer(this->_rend);
    SDL_DestroyWindow(this->_window);
    SDL_Quit();
}

void arcade::SDL2::loadSprite()
{
    this->_surface = IMG_Load("assets/player.png");
    this->_texture.push_back(SDL_CreateTextureFromSurface(this->_rend, this->_surface));
    SDL_FreeSurface(this->_surface);
    this->_surface = IMG_Load("assets/body.png");
    this->_texture.push_back(SDL_CreateTextureFromSurface(this->_rend, this->_surface));
    SDL_FreeSurface(this->_surface);
    this->_surface = IMG_Load("assets/wall.png");
    this->_texture.push_back(SDL_CreateTextureFromSurface(this->_rend, this->_surface));
    SDL_FreeSurface(this->_surface);
    this->_surface = IMG_Load("assets/bonus_a.png");
    this->_texture.push_back(SDL_CreateTextureFromSurface(this->_rend, this->_surface));
    SDL_FreeSurface(this->_surface);
    this->_surface = IMG_Load("assets/bonus_b.png");
    this->_texture.push_back(SDL_CreateTextureFromSurface(this->_rend, this->_surface));
    SDL_FreeSurface(this->_surface);
    this->_surface = IMG_Load("assets/enemy.png");
    this->_texture.push_back(SDL_CreateTextureFromSurface(this->_rend, this->_surface));
    SDL_FreeSurface(this->_surface);
}

int arcade::SDL2::getSpriteTexture(const arcade::common::SpriteType type)
{
    switch (type) {
        case common::SpriteType::PLAYER:
            return (0);
        case common::SpriteType::BODY:
            return (1);
        case common::SpriteType::WALL:
            return (2);
        case common::SpriteType::BONUS_A:
            return (3);
        case common::SpriteType::BONUS_B:
            return (4);
        case common::SpriteType::ENEMY:
            return (5);
        default:
            break;
    }
    return (-1);
}

void arcade::SDL2::displaySprites(const std::vector<common::Sprite> &sprites)
{
    std::string filepath;
    size_t pos;

    for (const auto &n: sprites) {
        this->_dest.x = n.position.x * SIZE_X;
        this->_dest.y = n.position.y * SIZE_Y;
        pos = getSpriteTexture(n.type);
        SDL_QueryTexture(this->_texture[pos], NULL, NULL, &this->_dest.w, &this->_dest.h);
        SDL_RenderCopy(this->_rend, this->_texture[pos], NULL, &this->_dest);
    }
}

void arcade::SDL2::displayTexts(const std::vector<common::Text> &texts)
{
    for (const auto &n: texts) {
        this->_font = TTF_OpenFont("assets/font.ttf", n.size);
        this->_surface = TTF_RenderText_Solid(this->_font, n.text.c_str(), this->_white);
        this->_text = SDL_CreateTextureFromSurface(this->_rend, this->_surface);
        this->_dest.x = n.position.x * SIZE_X;
        this->_dest.y = n.position.y * SIZE_Y;
        this->_dest.w = this->_surface->w;
        this->_dest.h = this->_surface->h;
        SDL_RenderCopy(this->_rend, this->_text, NULL, &this->_dest);
        SDL_DestroyTexture(this->_text);
        SDL_FreeSurface(this->_surface);
    }
}

void arcade::SDL2::playSound(const std::vector<common::Sound> &sounds)
{
    for (const auto &n: sounds) {
        (void) n;
    }
}

void arcade::SDL2::display(const common::Data &data)
{
    SDL_RenderClear(this->_rend);
    displaySprites(data.sprites);
    displayTexts(data.texts);
    playSound(data.sounds);
    SDL_RenderPresent(this->_rend);
    SDL_Delay(30);
}

std::optional<arcade::common::Input> arcade::SDL2::getInput()
{
    while (SDL_PollEvent(&this->_event)) {
        if (this->_event.type == SDL_QUIT) {
            return (common::Input::EXIT);
        } else if (this->_event.type == SDL_KEYDOWN) {

            switch (this->_event.key.keysym.scancode) {
                case SDL_SCANCODE_Q:
                    return (common::Input::EXIT);
                case SDL_SCANCODE_UP:
                    return (common::Input::UP);
                case SDL_SCANCODE_DOWN:
                    return (common::Input::DOWN);
                case SDL_SCANCODE_RIGHT:
                    return (common::Input::RIGHT);
                case SDL_SCANCODE_LEFT:
                    return (common::Input::LEFT);
                case SDL_SCANCODE_ESCAPE:
                    return (common::Input::BACK_MENU);
                case SDL_SCANCODE_R:
                    return (common::Input::RESTART);

                case SDL_SCANCODE_T:
                    return (common::Input::ACTION_1);
                case SDL_SCANCODE_Y:
                    return (common::Input::ACTION_2);
                case SDL_SCANCODE_U:
                    return (common::Input::SPECIAL_1);
                case SDL_SCANCODE_I:
                    return (common::Input::SPECIAL_2);
                case SDL_SCANCODE_G:
                    return (common::Input::NEXT_GAME);
                case SDL_SCANCODE_D:
                    return (common::Input::NEXT_LIBRARY);
                default:
                    break;
            }
        }
    }
    return std::nullopt;
}
