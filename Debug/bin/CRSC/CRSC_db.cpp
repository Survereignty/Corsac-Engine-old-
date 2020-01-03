#include "CRSC_db.h"

////////////////////////////////////////////////////////////////////////////////////////////

// Игровая сцена
CRSC_Scene::CRSC_Scene(){};
CRSC_Scene::CRSC_Scene(
    std::string     name,
    SDL_Renderer*   Renderer
) {
    this->name = name;
    this->Renderer = Renderer;
};
void CRSC_Scene::Methods(
    void (*callbackLoading)(),
    void (*callbackEvent)(),
    void (*callbackLoop)(),
    void (*callbackDestroy)()
) {
    cbload  = callbackLoading;
    cbevent = callbackEvent;
    cbloop  = callbackLoop;
    cbdest  = callbackDestroy;
}
void CRSC_Scene::Play()
{
    state = 1;
    Loading(cbload);
    while (state != 0)
    {
        Events(cbevent);
        Loop(cbloop);
    }
    Destroy(cbdest);
}
void CRSC_Scene::Stop(){state = 0;}
void CRSC_Scene::Loading(void (*callback)()){callback();}
void CRSC_Scene::Events(void (*callback)())
{
    while (SDL_PollEvent(&e) != 0) {
        if( e.type == SDL_QUIT )
        {
            Stop();
        }
        callback();
    }
}
void CRSC_Scene::Loop(void (*callback)())
{
    callback();
    SDL_RenderPresent(Renderer);
}
void CRSC_Scene::Destroy(void (*callback)()){callback();}
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