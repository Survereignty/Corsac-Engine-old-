#include <fstream>
#include <iostream>
#include <string>
#include "SDL2/SDL.h"

// Получить имя переменной
#define getName(v) #v;

class Config
{
public:
    Config();

    void GetDisplay();
    void init();

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

private:

    void createConfig();
    //Получить ключ ini строчки
    std::string getValueIni  (std::string s);
    // Получить значение ini строчки
    std::string getKeyIni    (std::string s);

    int         fpsScreen;

};

Config::Config()
{
    // Настройки игры по умолчанию
    // [Video]
    screenWidth     = 800;      // Ширина экрана
    screenHeight    = 600;      // Высота экрана
    fullScreen      = false;    // Полноэкранный режим: 0-нет 1-да
    presentvsync    = false;    // Вертикальная синхронизация
    fpsOut          = false;    // Ограничения по фпс
    maxFps          = 30;       // На какое число ограничить
    brigh           = 1.0;      // Цветовая гамма
    // [Audio]
    musicValume     = 10;       // Громкость музыки
}

void Config::init() {
    // SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    // MIX
    Mix_Init(MIX_INIT_MP3);
    // Проверяем существует ли файл config.ini
    std::ifstream  file;
    file.open("config.ini");

    if (!file) {
        createConfig();
    } else {
        GetDisplay();
        std::string s, key, value;
        while(std::getline(file, s))
        {
            if (s.find('['))
            {
                value = getValueIni(s);
                key = getKeyIni(s);

                if        (key == "screenWidth") {
                    screenWidth     = stoi(value);
                } else if (key == "screenHeight") {
                    screenHeight    = stoi(value);
                } else if (key == "fullScreen") {
                    fullScreen      = stoi(value);
                } else if (key == "presentvsync") {
                    presentvsync    = stoi(value);
                } else if (key == "fpsOut") {
                    fpsOut          = stoi(value);
                } else if (key == "maxFps") {
                    maxFps          = stoi(value);
                } else if (key == "musicValume") {
                    musicValume     = stoi(value);
                } else if (key == "brigh") {
                    brigh           = stoi(value);
                }
            }
        }
        createConfig();
    }
    file.close();
}

void Config::createConfig() {
    std::ofstream file ("config.ini");

    // Записываем конфиг
    file << "[Video]" << std::endl;
        file << "screenWidth="      + std::to_string(screenWidth)  + "   #Ширина экрана"  << std::endl;
        file << "screenHeight="     + std::to_string(screenHeight) + "   #Высота экрана"  << std::endl;
        file << "fullScreen="       + std::to_string(fullScreen)   + "   #Режим экрана"  << std::endl;
        file << "presentvsync="     + std::to_string(presentvsync) + "   #Вертикальная синхронизация"  << std::endl;
        file << "fpsOut="           + std::to_string(fpsOut)       + "   #Режим ограниченного фпс"  << std::endl;
        file << "maxFps="           + std::to_string(maxFps)       + "   #Максимальное кол-во фпс"  << std::endl;
        file << "brigh="            + std::to_string(brigh)        + "   #Цветовая гамма"  << std::endl;
    file << "[Audio]" << std::endl;
        file << "musicValume="      + std::to_string(musicValume)  + "   #Громкость музыки"  << std::endl;
}

// Получить ключ ini строчки
std::string Config::getKeyIni(std::string s)
{
    std::string l = "";
    for(int i = 0; s[i] != '='; i++){
        l += s[i];
    }
    return l;
}

// Получить значение ini строчки
std::string Config::getValueIni(std::string s)
{
    std::string l = "";
    for(int i = 0; s[i]; i++) {
        if(s[i] == '='){
            for(i++ ;s[i];i++){
                l += s[i];
            }
            break;
        }
    }
    return l;
}

// Не работает, за место данных о экране выдает рандомные числа
void Config::GetDisplay()
{
    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0, &dm);
        screenWidth = dm.w;
        screenHeight = dm.h;
        fpsScreen = dm.refresh_rate;
}