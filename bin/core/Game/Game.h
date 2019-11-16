#pragma once

#include "SDL2/SDL.h"
#include "GL/glew.h"

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
    GameState _gameState;
};
