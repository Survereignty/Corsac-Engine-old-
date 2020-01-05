#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
#include <sstream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_thread.h"

struct CRSC_LogsFlags
{
    bool        USE_TERMINAL    = true;
    bool        USE_FILE        = true;
    const char* PATH            = strcat(SDL_GetBasePath(), "logs.txt");
};

struct CRSC_GraphFlags
{
    IMG_InitFlags flags = IMG_INIT_PNG;
    std::string   pathToSprite = strcat(SDL_GetBasePath(), "data/sprites/");
    std::string   format = ".png";
    const char*   pathToFont = strcat(SDL_GetBasePath(), "data/font/18432.ttf");
};

struct CRSC_AudioFlags
{
    MIX_InitFlags flags = MIX_INIT_MP3;
    int frequency = MIX_DEFAULT_FREQUENCY; // Частота
    Uint16 format = MIX_DEFAULT_FORMAT;    // Формат
    int channels = 2;                      // Каналы
    int chunksize = 1024;                  // Размер
};

struct CRSC_GameInfo
{
    const char*     GameName; // Название игры
    const char*     OrgName;  // Название организации
    char*           GamePath; // Путь до каталога хранения пользовательских данных
    char*           UserPath; // Путь до каталога игры
};

// Настройки видео
struct CRSC_Video
{
    int     Width  = 1200;  // Ширина экрана
    int     Height = 800;   // Высота экрана
    bool    Full   = false;  // Полноэкранный режим:          0-нет 1-да
    bool    FpsOut = false; // Ограничения по фпс:           0-нет 1-да
    int     MaxFps = 30;    // На какое число ограничить фпс
    float   Brigh  = 1.0;   // Цветовая гамма
};

// Настройки звука
struct CRSC_Audio
{
    int     Main   = 75;  // Общая громкость:  0 - 100
    int     Music  = 75;  // Громкость музыки: 0 - 100
    int     Sounds = 75;  // Громкость звуков: 0 - 100

    bool muteMusic  = false;
    bool muteSounds = false;
};

// Настройки игры
struct CRSC_Gameplay{};

// Настройки управления
struct CRSC_Keys{};

// Игровая сцена
class CRSC_Scene
{
private:
    // Состояние сцены
    int state;
    // Загрузка сцены
    virtual void Loading() = 0;
    // Цикл событий
    virtual void Events() = 0;
    // Цикл сцены
    virtual void Loop() = 0;
    // Закрытие сцены
    virtual void Destroy() = 0;

public:
    SDL_Renderer* R;
    SDL_Event e;

    void Play(); // Запустить сцену
    void Stop(); // Остановить сцену

    CRSC_Scene();
    ~CRSC_Scene();
};

// Хранилище данных игры
class CRSC_Store
{
private:

public:
    CRSC_Store();
    ~CRSC_Store();
};