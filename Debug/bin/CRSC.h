#pragma once

#include "CRSC_lib.h"

// ------------------------ Структура пользовательских настроек приложения -------------------------- //
struct CRSC_Settings
{
    int     screenWidth;
    int     screenHeight;
    bool    fullScreen;
    bool    presentvsync;
    bool    fpsOut;
    int     maxFps;
    float   brigh;

    int     generalValume;
    int     musicValume;
    int     soundsValume;

    // Структура пользовательских настроек приложения
    //
    // [Video]
    // int     screenWidth;    // Ширина экрана
    // int     screenHeight;   // Высота экрана
    // bool    fullScreen;     // Полноэкранный режим:         0-нет 1-да
    // bool    presentvsync;   // Вертикальная синхронизация:  0-нет 1-да
    // bool    fpsOut;         // Ограничения по фпс:          0-нет 1-да
    // int     maxFps;         // На какое число ограничить
    // float   brigh;          // Цветовая гамма
    // [Audio]
    // int     generalValume;  // Общая громкость:             0 - 100
    // int     musicValume;    // Громкость музыки:            0 - 100
    // int     soundsValume;   // Громкость звуков:            0 - 100
    CRSC_Settings(
        int     screenWidth, // Ширина экрана
        int     screenHeight,
        bool    fullScreen,
        bool    presentvsync,
        bool    fpsOut,
        int     maxFps,
        float   brigh,

        int     generalValume,
        int     musicValume,
        int     soundsValume
    )
    {
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;
        this->fullScreen = fullScreen;
        this->presentvsync = presentvsync;
        this->fpsOut = fpsOut;
        this->maxFps = maxFps;
        this->brigh = brigh;

        this->generalValume = generalValume;
        this->musicValume = musicValume;
        this->soundsValume = soundsValume;
    };
};

// ------------------------ Объект настроек приложения -------------------------- //
class CRSC_Config
{
public:
    const char* path;           // Путь до config.ini

    CRSC_Settings* settings;     // Структура пользовательских настроек приложения

    // Инициализация Создаем/читаем файл
    void init(char *pathMain, CRSC_Settings* settings);

    CRSC_Config();
    ~CRSC_Config();
private:
    // Частота смены кадров монитора пользователя
    int fpsScreen;

    // Устанавливаем текущие параметры экрана пользователя
    void setDefault();;
};
// ------------------------ Объект настроек проиложения -------------------------- //

// ------------------------ Объект игровой сцены        -------------------------- //
// Объект сцены
class CRSC_Scene
{
public:

    SDL_Event e;

    void (*cbload)();   // Загрузка сцены
    void (*cbevent)();  // Цикл событий
    void (*cbloop)();   // Цикл сцены
    void (*cbdest)();   // Закрытие сцены

    // Запустить сцену
    void Play();
    // Остановить сцену
    void Stop();

    void Methods(void (*callbackLoading)(), void (*callbackEvent)(), void (*callbackLoop)(), void (*callbackDestroy)());
    CRSC_Scene();
    CRSC_Scene(std::string name, SDL_Renderer* render);
    ~CRSC_Scene();
private:
    // Состояние сцены
    SDL_Renderer* render;
    int state;
    std::string name;

    // Загрузка сцены
    void Loading(void (*callback)());

    // Цикл событий
    void Events(void (*callback)());

    // Цикл сцены
    void Loop(void (*callback)());

    // Закрытие сцены
    void Destroy(void (*callback)());
};

// ------------------------ Объект игровой сцены        -------------------------- //

// ------------------------ Объект игрового движка      -------------------------- //
class CRSC_Engine
{
private:
    // Устанавливаем настройки из конфига
    void setStartSettings();

    int countScene;
public:
    // Создает экземпляр Corsac Engine окна
    void create(const char* TitleProgram, CRSC_Settings* settings);
    CRSC_Scene CreateScene(std::string name);

    SDL_Window*     window;     // Контекст окна
    SDL_Renderer*   render;     // Контекст рендера
    TTF_Font*       font;       // Шрифт
    CRSC_Config     config;     // Настройки приложения
    char*           path;       // Путь до приложения

    CRSC_Engine();
    ~CRSC_Engine();
};

// Конструктор
CRSC_Engine CRSC_EngineCreate(const char* TitleProgram, CRSC_Settings* settings);
// ------------------------ Объект игрового движка      -------------------------- //