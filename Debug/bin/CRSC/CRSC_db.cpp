#include "CRSC_db.h"

////////////////////////////////////////////////////////////////////////////////////////////

// Игровая сцена
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
            if (e.type == SDL_QUIT)
            {
                Stop();
            }
            Events();
        }
        Loop();
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