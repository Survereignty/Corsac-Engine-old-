#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_vulkan.h"
//#include "../Vulkan/Vulkan.cpp"
#include <iostream>
#include <string>

enum class GameState {PLAY, EXIT};

class Game
{
public:
    Game();
    ~Game();

    void run();


private:
    void initSystems();
    void gameLoop();
    void processInput();
    void drawGame();

    SDL_Window* _window;
    int _screenWidth;
    int _screenHeight;
    const char* _title;
    Mix_Music* _music;
    GameState _gameState;
    //Vulkan* renderer;
};
