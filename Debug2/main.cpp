#include "./bin/CRSC.h"

CRSC_Video* Video = new CRSC_Video
{
    screenWidth:    800,
    screenHeight:   600,
    fullScreen:     false,
    presentvsync:   false,
    fpsOut:         false,
    maxFps:         30,
    brigh:          1.0
};
CRSC_Audio* Audio  = new CRSC_Audio
{
    generalValume:  75,
    musicValume:    75,
    soundsValume:   75
};
CRSC_Gameplay*  Gameplay    = new CRSC_Gameplay{};
CRSC_Keys*      Keys        = new CRSC_Keys{};

CRSC_Settings*      Settings        = new CRSC_Settings(Video, Audio, Gameplay, Keys);

CRSC_ConfigFlags*   ConfigFlags     = new CRSC_ConfigFlags
{
    CRSC_AUTO_SETTINGS_FIRST_SETUP: false,
    CRSC_SAVE_SETTINGS:             true,
    CRSC_READ_SETTINGS:             false,
};

CRSC_LogsFlags* LogsFlags = new CRSC_LogsFlags
{
    USE_GAME: true,
    USE_TERMINAL: true,
    USE_FILE: true,
    PATH: "logs.txt"
};
CRSC_Log* Log = new CRSC_Log(LogsFlags);

CRSC_Config* Config = new CRSC_Config("TestGame","Corsac", Settings, ConfigFlags, Log);

CRSC_SDL* SDL = new CRSC_SDL(Config, SDL_INIT_EVERYTHING, SDL_WINDOW_SHOWN, SDL_RENDERER_PRESENTVSYNC);
CRSC_Mix* Mix = new CRSC_Mix(Config, MIX_INIT_MP3, MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
CRSC_Img* Img = new CRSC_Img(Config, IMG_INIT_PNG);
CRSC_Ttf* Ttf = new CRSC_Ttf(Config);

CRSC_Engine* Engine = new CRSC_Engine(SDL, Mix, Img, Ttf);

int main(int argc, char const *argv[])
{
    Config->GamePath = "";

    Engine->Setup();

    SDL_Delay(3000);

    return 0;
};