#pragma once

#include "CRSC_lib.h"

// ------------------------ Объект настроек проиложения -------------------------- //
class CRSC_Config
{
public:
    const char* path;       // Путь до config.ini
    // [Video]
    int     screenWidth;    // Ширина экрана
    int     screenHeight;   // Высота экрана
    bool    fullScreen;     // Полноэкранный режим: 0-нет 1-да
    bool    presentvsync;   // Вертикальная синхронизация
    bool    fpsOut;         // Ограничения по фпс
    int     maxFps;         // На какое число ограничить
    float   brigh;          // Цветовая гамма
    // [Audio]
    int     generalValume;  // Общая громкость
    int     musicValume;    // Громкость музыки
    int     soundsValume;   // Громкость звуков

    // Инициализация Создаем/читаем файл
    void init();

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

    void (*cbload)();   // Загрузка сцены
    void (*cbloop)();   // Цикл сцены
    void (*cbdest)();   // Закрытие сцены

    // Запустить сцену
    void Play();
    // Остановить сцену
    void Stop();

    CRSC_Scene();
    CRSC_Scene(void (*callbackLoading)(), void (*callbackLoop)(), void (*callbackDestroy)());
    ~CRSC_Scene();
private:
    // Состояние сцены
    int state;

    // Загрузка сцены
    void Loading(void (*callback)());

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
    void create(const char* TitleProgram);
    CRSC_Scene CreateScene(void (*callbackLoading)(), void (*callbackLoop)(), void (*callbackDestroy)());

    SDL_Window*     window;     // Контекст окна
    SDL_Renderer*   render;     // Контекст рендера
    CRSC_Config     config;     // Настройки приложения
    CRSC_Scene     *scenes;

    CRSC_Engine();
    ~CRSC_Engine();
};

// Конструктор
CRSC_Engine CRSC_EngineCreate(const char* TitleProgram);
// ------------------------ Объект игрового движка      -------------------------- //