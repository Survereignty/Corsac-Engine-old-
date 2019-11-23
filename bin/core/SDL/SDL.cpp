#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

#include "Config/Config.cpp"

class SDL
{
private:

public:
    SDL_Window*     window;
    SDL_Renderer*   render;
    Config          config;

    void init(const char* title);
    void setStartSettings();

    SDL();
    ~SDL();
};

SDL::SDL()
{
    window = nullptr;
    render = nullptr;
}

SDL::~SDL()
{
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    SDL_Quit();
}

void SDL::init(const char* title) {
    config.init();
    // Window

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    if(window == nullptr) {
        printf("SDL_Window: %s\n", SDL_GetError());
    }

    SDL_RendererFlags flags = SDL_RENDERER_ACCELERATED;
    if (config.presentvsync) {
        flags = SDL_RENDERER_PRESENTVSYNC, SDL_RENDERER_ACCELERATED;
    }

    // Render
    render = SDL_CreateRenderer(
        window,
        -1,
        flags
    );
    if (render == nullptr){
        printf("SDL_Render: %s\n", SDL_GetError());
    }

    // Устанавливаем настройки из конфига
    setStartSettings();

    // Настраиваем качество звука
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

}

void SDL::setStartSettings() {
    //SDL_SetWindowSize(window, config.screenWidth, config.screenHeight);
    if (config.fullScreen) {
        SDL_SetWindowBordered(window, SDL_FALSE);
        SDL_SetWindowFullscreen(window, 0);
        SDL_SetWindowGrab(window, SDL_TRUE);
    }
    SDL_SetWindowBrightness(window, config.brigh);
}
