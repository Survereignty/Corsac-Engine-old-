#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

// Режим работы
enum CRSC_Mode {
    DEBUG,  // Будут выводиться различная информация о работе библиотеки в терминал
    RELEASE // Отсутсвие записей в терминал
};

// Типы ошибок, выбраный тип будет писаться в начале ошибки
enum typeLog {
    INFO,
    WARNING,
    ERROR,
    CRASH,
    CLOSE,
    LOADING,
    COMPLETED
};

// Выбор к какой библеотеки относиться ошибка
enum typeLib {
    CRSC,   // Corsac Engine
    SDL,    // SDL2
    MIX,    // SDL2_Mix
    IMG     // SDL2_IMG
};

// Получить ключ ini строчки
std::string getKeyIni(std::string s);

// Получить значение ini строчки
std::string getValueIni(std::string s);

// Проверить файл на существование
int CRSC_CheckIni(const char* path);

// Создать файл и записать туда vector<std::string>
std::ofstream CRSC_CreateAndWrite(const char* path, std::vector<std::string> elems);

// Прочитать ini файл
std::map <std::string, std::string> CRSC_ReadIni(const char* path);

// Установить ошибку
void CRSC_setLog(
    // Текст
    const char* value,
    // Тип важности
    typeLog     type,
    // Тип библеотеки
    typeLib     typeL
);
