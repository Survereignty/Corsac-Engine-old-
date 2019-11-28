#pragma once

#include "CRSC_Func.h"
#include "SDL2/SDL_thread.h"

// Объект настроек проиложения
class CRSC_Config
{
public:
    const char* path;
    // [Video]
    int     screenWidth;
    int     screenHeight;
    bool    fullScreen;
    bool    presentvsync;
    bool    fpsOut;
    int     maxFps;
    float   brigh;
    // [Audio]
    int     musicValume;

    CRSC_Config();

    // Инициализация Создаем/читаем файл
    void init(const char* p);

    ~CRSC_Config();
private:
    // Частота смены кадров монитора пользователя
    int fpsScreen;
    // Устанавливаем текущие разрешение экрана пользователя
    void setDefault();;
};

class CRSC_Engine
{
private:
    const char* title;      // Титульник окна
    const char* configPath; // Путь до конфиг файла
    const char* logsPath;   // Путь до файла логов

    // Инициализация подсистем
    void initSystem();

    // Устанавливаем настройки из конфига
    void setStartSettings();

public:
    // Создает экземпляр Corsac Engine окна
    void create(const char* TitleProgram);

    SDL_Window*     window;     // Контекст окна
    SDL_Renderer*   render;     // Контекст рендера
    CRSC_Config     settings;   // Настройки приложения

    CRSC_Engine();
    ~CRSC_Engine();
};

// Конструктор движка
CRSC_Engine CRSC_EngineCreate(const char* TitleProgram);

// Состояние сцены
enum State {
    EXIT,
    RUN
};

// Объект сцены
class CRSC_Scene
{
public:

    void (*cbload)();
    void (*cbloop)();
    void (*cbdest)();

    CRSC_Scene(void (*callbackLoading)(), void (*callbackLoop)(), void (*callbackDestroy)());

    void Play();

    ~CRSC_Scene();

    void Stop();
private:
    State state = RUN;

    void Loading(void (*callback)());

    void Loop(void (*callback)());

    void Destroy(void (*callback)());
};

// Конструктор сцены
CRSC_Scene CRSC_SceneCreate(void (*callbackLoading)(), void (*callbackLoop)(), void (*callbackDestroy)());