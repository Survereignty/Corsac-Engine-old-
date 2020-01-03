#pragma once

#include "CRSC_db.h"

std::ofstream CRSC_CreateAndWrite(const char* path, std::string elem);

// Центр хранения и управления логами
class CRSC_Logs
{
private:
    CRSC_LogsFlags flags;
public:
    std::map<std::string, std::string> Logs;
    // Установить ошибку
    void Set(std::string info, std::string error);

    CRSC_Logs();
    ~CRSC_Logs();
};

// Центр управления SDL2
class CRSC_Sdl
{
private:
    unsigned int        SdlFlags;   // Флаги для SDL2
    SDL_WindowFlags     WinFlags;   // Флаги для Окна
    SDL_RendererFlags   RenFlags;   // Флаги для Рендера
public:
    SDL_Window*     Window;         // Контекст окна
    SDL_Renderer*   Renderer;       // Контекст рендера

    int Init();
    int CreateRenderer();
    int CreateWindow(
        const char* GameName,
        int & Width,
        int & Height
    );

    CRSC_Sdl();
    ~CRSC_Sdl();
};

// Центр управления SDL_IMG
class CRSC_Img
{
private:
    IMG_InitFlags ImgFlags; // Флаги для SDL_IMG
public:
    int Init();

    CRSC_Img();
    ~CRSC_Img();
};

// Центр управления SDL_MIX
class CRSC_Mix
{
private:
    CRSC_AudioFormat Format;
public:
    int Init();

    CRSC_Mix();
    ~CRSC_Mix();
};

// Центр управления SDL_Ttf
class CRSC_Ttf
{
private:

public:
    int Init();

    CRSC_Ttf();
    ~CRSC_Ttf();
};

// Центр управления
class CRSC_Engine
{
private:
    CRSC_Logs Logs; // Центр хранения и управления логами

    CRSC_Sdl Sdl; // Центр управления SDL2
    CRSC_Img Img; // Центр управления SDL_IMG
    CRSC_Mix Mix; // Центр управления SDL_MIX
    CRSC_Ttf Ttf; // Центр управления SDL_Ttf

    void Setup();      // Запустить игру
public:
    CRSC_Engine(const char* GameName, const char* OrgName);
    ~CRSC_Engine();

    void setAutoSizes(); // Определить экран игрока и установить размеры
    void setFullScreen(bool permanently = true); // Установить настройки

    CRSC_Scene CreateScene(std::string name);   // Создать сцену

    CRSC_Store    Store;   // Хранилище данных игры
    CRSC_GameInfo Info;    // Информация о проекте

    CRSC_Video    Video;    // Настройки Видео
    CRSC_Audio    Audio;    // Настройки Аудио
    CRSC_Gameplay Gameplay; // Найстройки Игры
    CRSC_Keys     Keys;     // Найстройки Клавиш
};

// Создание экземпляра игрового движка
CRSC_Engine CRSC_Init(const char* GameName, const char* OrgName);