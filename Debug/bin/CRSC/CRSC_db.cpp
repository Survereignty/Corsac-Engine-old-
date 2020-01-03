#include "CRSC_db.h"

////////////////////////////////////////////////////////////////////////////////////////////

// Игровая сцена
CRSC_Scene::CRSC_Scene(
    SDL_Renderer*   Renderer
) {
    state = 0;
    this->Renderer = Renderer;
};
CRSC_Scene::CRSC_Scene()
{
    state = 0;
};
void CRSC_Scene::Play()
{
    state = 1;
    Loading();
    while (state != 0)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                Stop();
            }
            Events();
        }
        Loop();
        SDL_RenderPresent(Renderer);
    }
    Destroy();
}
void CRSC_Scene::Stop(){state = 0;}
CRSC_Scene::~CRSC_Scene(){};

////////////////////////////////////////////////////////////////////////////////////////////

// Хранилище данных игры
CRSC_Store::CRSC_Store()
{

};
CRSC_Store::~CRSC_Store()
{

};

////////////////////////////////////////////////////////////////////////////////////////////