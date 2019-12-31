#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_thread.h"

// Настройки видео
struct CRSC_Video
{
    int     screenWidth;    // Ширина экрана
    int     screenHeight;   // Высота экрана
    bool    fullScreen;     // Полноэкранный режим:         0-нет 1-да
    bool    presentvsync;   // Вертикальная синхронизация:  0-нет 1-да
    bool    fpsOut;         // Ограничения по фпс:          0-нет 1-да
    int     maxFps;         // На какое число ограничить фпс
    float   brigh;          // Цветовая гамма
};

// Настройки звука
struct CRSC_Audio
{
    int     generalValume;  // Общая громкость:             0 - 100
    int     musicValume;    // Громкость музыки:            0 - 100
    int     soundsValume;   // Громкость звуков:            0 - 100
};

// Настройки игры
struct CRSC_Gameplay{};

// Настройки управления
struct CRSC_Keys{};

// Объект для сохранения
struct CRSC_SaveSettings
{
    CRSC_Video V;
    CRSC_Audio A;
    CRSC_Gameplay G;
    CRSC_Keys K;
};

struct CRSC_LogsFlags
{
    bool USE_GAME;
    bool USE_TERMINAL;
    bool USE_FILE;
    const char* PATH;
};

struct CRSC_ConfigFlags
{
    bool CRSC_AUTO_SETTINGS_FIRST_SETUP;
    bool CRSC_SAVE_SETTINGS;
    bool CRSC_READ_SETTINGS;
};

// Проверить файл на существование
int CRSC_CheckFile(const char* path);

std::ofstream CRSC_CreateAndWrite(const char* path, std::string elem);
