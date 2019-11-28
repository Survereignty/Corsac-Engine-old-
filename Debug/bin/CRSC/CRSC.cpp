#include "CRSC.h"

CRSC_Config::CRSC_Config() {
    path = NULL;
    // Настройки приложения по умолчанию
    // [Video]
    screenWidth     = 800;      // Ширина экрана
    screenHeight    = 600;      // Высота экрана

    fullScreen      = false;    // Полноэкранный режим: 0-нет 1-да
    presentvsync    = false;    // Вертикальная синхронизация
    fpsOut          = false;    // Ограничения по фпс
    maxFps          = 30;       // На какое число ограничить
    brigh           = 1.0;      // Цветовая гамма
    // [Audio]
    musicValume     = 10;       // Громкость музыки    path = NULL;
};

    // Инициализация Создаем/читаем файл
void CRSC_Config::init(const char* p) {
    path = p;
    std::map <std::string, std::string> data;
    if (CRSC_CheckIni(path)) {
        setDefault();
        std::vector<std::string> settings = {
        "[Video]",
        "screenWidth="      + std::to_string(screenWidth),
        "screenHeight="     + std::to_string(screenHeight),
        "fullScreen="       + std::to_string(fullScreen),
        "presentvsync="     + std::to_string(presentvsync),
        "fpsOut="           + std::to_string(fpsOut),
        "maxFps="           + std::to_string(maxFps),
        "brigh="            + std::to_string(brigh),
        "[Audio]",
        "musicValume="      + std::to_string(musicValume)
        };
        CRSC_CreateAndWrite(path, settings);
    }
    data = CRSC_ReadIni(path);

    screenWidth = stoi(data["screenWidth"]);
    screenHeight = stoi(data["screenHeight"]);
    fullScreen = stoi(data["fullScreen"]);
    presentvsync = stoi(data["presentvsync"]);
    fpsOut = stoi(data["fpsOut"]);
    maxFps = stoi(data["maxFps"]);
    brigh = stoi(data["brigh"]);
    musicValume = stoi(data["musicValume"]);

    CRSC_setLog("Config", COMPLETED, CRSC);
};

CRSC_Config::~CRSC_Config() {
    path = NULL;
    CRSC_setLog("Config", CLOSE, CRSC);
};

// Устанавливаем текущие разрешение экрана пользователя
void CRSC_Config::setDefault() {
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
        screenWidth = dm.w;
        screenHeight = dm.h;
        fpsScreen = dm.refresh_rate;
};

CRSC_Engine::CRSC_Engine()
{
    title = NULL;       // Заголовок окна
    configPath = NULL;  // Путь до конфиг файла
    logsPath = NULL;    // Путь до лог файла
    window = NULL;      // Контекст окна
    render = NULL;      // Контекст рендера
};

// Создает экземпляр Corsac Engine окна
void CRSC_Engine::create(const char* TitleProgram) {
    char *gamePath = SDL_GetBasePath();
    configPath = strcat(gamePath, "Config.ini");
    gamePath = SDL_GetBasePath();
    logsPath = strcat(gamePath, "Debug.log");
    CRSC_setLog("Engine", LOADING, CRSC);
    title =  TitleProgram;
    initSystem();
};

// Инициализация подсистем
void CRSC_Engine::initSystem() {
    // SDL
    !SDL_Init(SDL_INIT_EVERYTHING) ? CRSC_setLog("SDL", COMPLETED, CRSC) : CRSC_setLog("SDL not init", CRASH, SDL);

    // MIX
    !Mix_Init(MIX_INIT_MP3) ? CRSC_setLog("MIX", COMPLETED, CRSC) : CRSC_setLog("MIX not init", CRASH, MIX);

    // IMG
    IMG_Init(IMG_INIT_PNG) ? CRSC_setLog("IMG", COMPLETED, CRSC) : CRSC_setLog("IMG not init", CRASH, IMG);

    settings.init(configPath);

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        settings.screenWidth,
        settings.screenHeight,
        SDL_WINDOW_SHOWN
    );
    window == NULL ? CRSC_setLog("Window not create", CRASH, SDL) : CRSC_setLog("Window", COMPLETED, CRSC);

    SDL_RendererFlags flags = SDL_RENDERER_ACCELERATED;
    if (settings.presentvsync) {
        flags = SDL_RENDERER_PRESENTVSYNC, SDL_RENDERER_ACCELERATED;
    }

    // Render
    render = SDL_CreateRenderer(
        window,
        -1,
        flags
    );
    render == nullptr ? CRSC_setLog("Render not create", CRASH, SDL) : CRSC_setLog("Render", COMPLETED, CRSC);
    // Устанавливаем настройки из конфига
    setStartSettings();

    // Настраиваем качество звука
    !Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) ? CRSC_setLog("Audio", COMPLETED, CRSC) : CRSC_setLog("Audio not init", CRASH, MIX);

    CRSC_setLog("Engine", COMPLETED , CRSC);
};

// Устанавливаем настройки из конфига
void CRSC_Engine::setStartSettings() {
    if (settings.fullScreen) {
        SDL_SetWindowBordered(window, SDL_FALSE);
        SDL_SetWindowFullscreen(window, 0);
        SDL_SetWindowGrab(window, SDL_TRUE);
    }
    SDL_SetWindowBrightness(window, settings.brigh);
};

CRSC_Engine::~CRSC_Engine()
{
    title = NULL;
    configPath = NULL;
    logsPath = NULL;
    Mix_CloseAudio();
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    CRSC_setLog("Engine", CLOSE, CRSC);
};

CRSC_Engine CRSC_EngineCreate(const char* TitleProgram) {
    CRSC_Engine engine;
    engine.create(TitleProgram);
    return engine;
};

CRSC_Scene::CRSC_Scene(void (*callbackLoading)(), void (*callbackLoop)(), void (*callbackDestroy)()) {
    cbload = callbackLoading;
    cbloop = callbackLoop;
    cbdest = callbackDestroy;
};

void CRSC_Scene::Play() {
    Loading(cbload);
    while (state != EXIT)
    {
        Loop(cbloop);
    }
    Destroy(cbdest);
}

CRSC_Scene::~CRSC_Scene() {

};

void CRSC_Scene::Stop() {
    state = EXIT;
}


void CRSC_Scene::Loading(void (*callback)()) {
    callback();
}

void CRSC_Scene::Loop(void (*callback)()) {
    callback();
}

void CRSC_Scene::Destroy(void (*callback)()) {
    callback();
}

// Конструктор сцены
CRSC_Scene CRSC_SceneCreate(void (*callbackLoading)(), void (*callbackLoop)(), void (*callbackDestroy)()) {
    CRSC_Scene scene(callbackLoading, callbackLoop, callbackDestroy);
    return scene;
}
