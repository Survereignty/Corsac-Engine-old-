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

class CRSC_Timer
{
private:
    // Время старта таймера
    Uint32 mStartTicks;
    // Время остановки таймера
    Uint32 mPausedTicks;

    // Статус таймера
    bool mPaused;
    bool mStarted;
public:
    CRSC_Timer();
    ~CRSC_Timer();

    void start();   // Запустить
    void stop();    // Остановить
    void pause();   // Пауза
    void unpause(); // Убрать паузу

    Uint32 getTicks(); // Текущие время

    bool isStarted(); // Запущен?
    bool isPaused();  // На паузе?
};

// Объект
class CRSC_Texture
{
private:
public:
    // Установить цветовой фильтр
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    // Установить прозрачность
    void setAlpha(Uint8 alpha);

    double angle;
    SDL_Point* center;
    SDL_RendererFlip flip;
    SDL_Texture* tex;
    SDL_Rect* rect;
    SDL_Rect* clip = NULL;
    CRSC_Texture(SDL_Rect* rect, SDL_Texture* tex);
    ~CRSC_Texture();
};


// Центр управления SDL_IMG
class CRSC_Graph
{
private:
    SDL_Renderer* R;
    CRSC_Logs* Logs; // Центр хранения и управления логами

    CRSC_GraphFlags Flags;

    std::vector<CRSC_Texture*> texs;

    TTF_Font * Font;

    void Init(SDL_Renderer* R, CRSC_Logs* Logs);
public:
    CRSC_Texture* CreateObject(std::string path, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    CRSC_Texture* CreateText(std::string text, Uint8 r, Uint8 g, Uint8 b, int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void DrawingObjects();
    void DestroyObjects();

    CRSC_Graph();
    ~CRSC_Graph();

    friend class CRSC_Engine;
};

// Центр управления SDL_MIX
class CRSC_Mix
{
private:
    CRSC_AudioFlags Format;
public:
    int Init();

    CRSC_Mix();
    ~CRSC_Mix();
};

// Центр управления
class CRSC_Engine
{
private:
    CRSC_Logs Logs; // Центр хранения и управления логами

    CRSC_Sdl Sdl; // Центр управления SDL2
    CRSC_Graph Graph; // Центр управления SDL_IMG
    CRSC_Mix Mix; // Центр управления SDL_MIX

    void Setup();      // Запустить игру
public:

    CRSC_Engine(const char* GameName, const char* OrgName);
    ~CRSC_Engine();

    SDL_Renderer*   getRenderer();
    CRSC_Logs*      getLogs();
    CRSC_Graph*       getGraph();

    void setAutoSizes(); // Определить экран игрока и установить размеры
    void setFull(bool permanently = true); // Установить настройки

    CRSC_Store    Store;   // Хранилище данных игры
    CRSC_GameInfo Info;    // Информация о проекте

    CRSC_Video    Video;    // Настройки Видео
    CRSC_Audio    Audio;    // Настройки Аудио
    CRSC_Gameplay Gameplay; // Найстройки Игры
    CRSC_Keys     Keys;     // Найстройки Клавиш
};

// Создание экземпляра игрового движка
CRSC_Engine CRSC_Init(const char* GameName, const char* OrgName);