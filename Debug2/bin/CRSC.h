#pragma once

#include "CRSC_lib.h"

// Пользовательские настройки игры
class CRSC_Settings
{
private:

public:
    CRSC_Video*     Video;      // Настройки видео
    CRSC_Audio*     Audio;      // Настройки звука
    CRSC_Gameplay*  Gameplay;   // Настройки игры
    CRSC_Keys*      Keys;       // Настройки управления

    CRSC_Settings();
    CRSC_Settings
    (
        CRSC_Video*     Video,
        CRSC_Audio*     Audio,
        CRSC_Gameplay*  Gameplay,
        CRSC_Keys*      Keys
    );
    ~CRSC_Settings();

    const char* _path;      // Путь до файла с настройками пользователя

    int Save(); // Сохранить текущие настройки
    int Set();  // Применить сохраненные настройки
};

// Логирование
class CRSC_Log
{
private:
    CRSC_LogsFlags* LogsFlags;
public:
    CRSC_Log
    (
        CRSC_LogsFlags* LogsFlags
    );
    ~CRSC_Log();

    std::map<std::string, std::string> Logs;

    void Error(std::string info, std::string error);
    void Info(std::string info);
    void Crash(std::string info, std::string error);
};


// Корневые настройки игры
class CRSC_Config
{
private:
    int fpsScreen;              // Частота смены кадров монитора пользователя

    CRSC_ConfigFlags*   ConfigFlags;        // Флаги для CRSC

    void FindAndSetRecommendedSettings();   // Найти и установить настройки по умолчанию
public:
    CRSC_Settings*  Settings;   // Пользовательские настройки игры
    CRSC_Log*            Log;   // Логирование

    const char*     GameName;           // Название игры
    const char*     OrganizationName;   // Название организации

    char*     UserPath;      // Путь до каталога хранения пользовательских данных
    char*     GamePath;      // Путь до каталога игры

    CRSC_Config
    (
        const char*         GameName,        // Название игры
        const char*         OrganizationName,// Название организации
        CRSC_Settings*      Settings,        // Пользовательские настройки игры
        CRSC_ConfigFlags*   CrscFlags,       // Флаги для CRSC
        CRSC_Log*           Log              // Логирование
    );
    ~CRSC_Config();

    void UseDefProfile();  // Использовать профиль по умолчанию
    void CreateProfile();  // Создать профиль
    void SaveProfile();    // Сохранить профиль
    void LoadProfile();    // Загрузить профиль
};

// Настройки Img
class CRSC_Img
{
private:
    CRSC_Config*    Config;
    IMG_InitFlags   ImgFlags;       // Флаги для SDL_IMG
public:
    CRSC_Img
    (
        CRSC_Config*    Config,
        IMG_InitFlags   ImgFlags    // Флаги для SDL_IMG
    );
    ~CRSC_Img();

    int  _init(); // Инициализация Img
};

// Настройки Ttf
class CRSC_Ttf
{
private:
    CRSC_Config*    Config;
public:
    CRSC_Ttf
    (
        CRSC_Config*    Config
    );
    ~CRSC_Ttf();

    int  _init(); // Инициализация Ttf
};

// Настройки Mix
class CRSC_Mix
{
private:
    CRSC_Config*    Config;
    MIX_InitFlags   MixFlags;   // Флаги для SDL_MIX

    int frequency;  // Частота
    Uint16 format;  // Формат
    int channels;   // Каналы
    int chunksize;  // Размер
public:
    CRSC_Mix
    (
        CRSC_Config*    Config,
        MIX_InitFlags   MixFlags,   // Флаги для SDL_MIX
        int frequency,  // Частота
        Uint16 format,  // Формат
        int channels,   // Каналы
        int chunksize   // Размер
    );
    ~CRSC_Mix();

    int  _init();          // Инициализация Mix
    void SetSounds();     // Активировать звуки
};

// Настройки SDL2
class CRSC_SDL
{
private:
    CRSC_Config*    Config; // Корневые настройки игры

    unsigned int        SdlFlags;   // Флаги для SDL2
    SDL_WindowFlags     WinFlags;   // Флаги для Окна
    SDL_RendererFlags   RenFlags;   // Флаги для Рендера

    SDL_Window*     Window;         // Контекст окна
    SDL_Renderer*   Renderer;       // Контекст рендера
public:
    CRSC_SDL
    (
        CRSC_Config*        Config,     // Корневые настройки игры
        unsigned int        SdlFlags,   // Флаги для SDL2
        SDL_WindowFlags     WinFlags,   // Флаги для Окна
        SDL_RendererFlags   RenFlags    // Флаги для Рендера
    );
    ~CRSC_SDL();

    void _init();             // Инициализация SDL2
    void _createWindow();     // Создание Окна
    void _createRenderer();   // Создание Рендера
};

// Игровой движек
class CRSC_Engine
{
private:
    CRSC_SDL* SDL;
    CRSC_Mix* Mix;
    CRSC_Img* Img;
    CRSC_Ttf* Ttf;
public:
    CRSC_Engine
    (
        CRSC_SDL* SDL,  // Настройки SDL2
        CRSC_Mix* Mix,  // Настройки Mix
        CRSC_Img* Img,  // Настройки Img
        CRSC_Ttf* Ttf   // Настройки Ttf
    );
    ~CRSC_Engine();
    int Setup();    // Запустить игру
};

