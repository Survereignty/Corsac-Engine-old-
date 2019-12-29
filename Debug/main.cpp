#include "./bin/CRSC.h"

CRSC_Settings* DefaultSettings = new CRSC_Settings(
    // [Video]
    800,    // Ширина экрана
    600,    // Высота экрана
    0,      // Полноэкранный режим:         0-нет 1-да
    0,      // Вертикальная синхронизация:  0-нет 1-да
    0,      // Ограничения по фпс:          0-нет 1-да
    30,     // На какое число ограничить
    1.0,    // Цветовая гамма
    // [Audio]
    75,     // Общая громкость:             0 - 100
    75,     // Громкость музыки:            0 - 100
    75      // Громкость звуков:            0 - 100
);

CRSC_Engine Engine = CRSC_EngineCreate("TestGame", DefaultSettings);

CRSC_Scene Menu = Engine.CreateScene("Menu");

void Load()
{

};

void Events()
{

};

void Loop()
{
    SDL_RenderClear(Engine.render);
    SDL_RenderPresent(Engine.render);
};

void Destroy()
{

};

int main(int argc, char const *argv[])
{
    Menu.Methods(Load, Events, Loop, Destroy);
    Menu.Play();

    return 0;
}
