#include "./bin/CRSC.h"

CRSC_Engine engine = CRSC_EngineCreate("SkyFort");

SDL_Texture* texture;

void Load() {
    SDL_Surface* surface = LoadSurface("./data/sprites/player.png");
    texture = LoadTexture(engine.render, surface);
};

void Loop() {
    SDL_RenderClear(engine.render);
    SDL_RenderCopy(engine.render, texture, NULL, NULL);
    SDL_RenderPresent(engine.render);
};

void Destroy() {
    SDL_DestroyTexture(texture);
}

CRSC_Scene Menu = engine.CreateScene(Load, Loop, Destroy);

int threadFunction( void* data )
{
    printf("Running");
    SDL_Delay(3000);
    Menu.Stop();
    return 0;
}

int main(int argc, char const *argv[])
{
    SDL_Thread* threadID = SDL_CreateThread( threadFunction, "LazyThread", (void*)NULL);
    Menu.Play();

    return 0;
}
