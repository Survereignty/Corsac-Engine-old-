#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_thread.h"

// Получить поверхность
SDL_Surface* LoadSurface(std::string path);

// Получить текстуру
SDL_Texture* LoadTexture(SDL_Renderer* render, SDL_Surface* surface);

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