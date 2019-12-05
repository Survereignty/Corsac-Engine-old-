#include "CRSC.h"

// ------------------------ Объект настроек проиложения -------------------------- //
CRSC_Config::CRSC_Config()
{
    // PUBLIC
    // [Video]
    screenWidth     = 800;      // Ширина экрана
    screenHeight    = 600;      // Высота экрана
    fullScreen      = false;    // Полноэкранный режим: 0-нет 1-да
    presentvsync    = false;    // Вертикальная синхронизация
    fpsOut          = false;    // Ограничения по фпс
    maxFps          = 30;       // На какое число ограничить
    brigh           = 1.0;      // Цветовая гамма
    // [Audio]
    generalValume   = 75;       // Общая громкость
    musicValume     = 75;       // Громкость музыки
    soundsValume    = 75;       // Громкость звуков

    // PRIVATE
    fpsScreen       = 60;       // Частота смены кадров монитора пользователя
};

CRSC_Config::~CRSC_Config()
{

};

// Инициализация Создаем/читаем файл
void CRSC_Config::init()
{
    // Путь до config.ini
    path = strcat(SDL_GetBasePath(), "Config.ini");

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
            "generalValume="    + std::to_string(generalValume),
            "musicValume="      + std::to_string(musicValume),
            "soundsValume="     + std::to_string(soundsValume)
        };

        CRSC_CreateAndWrite(path, settings);
    }

    data = CRSC_ReadIni(path);

    screenWidth     = stoi(data["screenWidth"]);
    screenHeight    = stoi(data["screenHeight"]);
    fullScreen      = stoi(data["fullScreen"]);
    presentvsync    = stoi(data["presentvsync"]);
    fpsOut          = stoi(data["fpsOut"]);
    maxFps          = stoi(data["maxFps"]);
    brigh           = stoi(data["brigh"]);
    generalValume   = stoi(data["generalValume"]);
    musicValume     = stoi(data["musicValume"]);
    soundsValume    = stoi(data["soundsValume"]);
};

// Устанавливаем текущие параметры экрана пользователя
void CRSC_Config::setDefault()
{
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
        screenWidth = dm.w;
        screenHeight = dm.h;
        fpsScreen = dm.refresh_rate;
};
// ------------------------ Объект настроек проиложения -------------------------- //

// ------------------------ Объект игровой сцены        -------------------------- //
CRSC_Scene::CRSC_Scene(
    void (*callbackLoading)(),
    void (*callbackLoop)(),
    void (*callbackDestroy)()
) {
    cbload = callbackLoading;
    cbloop = callbackLoop;
    cbdest = callbackDestroy;
};

CRSC_Scene::CRSC_Scene() {
    cbload = NULL;
    cbloop = NULL;
    cbdest = NULL;
};

CRSC_Scene::~CRSC_Scene()
{
    std::cout << "destrscene" << std::endl;
};

// Запустить сцену
void CRSC_Scene::Play()
{
    state = 1;
    Loading(cbload);
    while (state != 0)
    {
        Loop(cbloop);
    }
    Destroy(cbdest);
}

// Остановить сцену
void CRSC_Scene::Stop()
{
    state = 0;
}

// Загрузка сцены
void CRSC_Scene::Loading(void (*callback)())
{
    callback();
}

// Цикл сцены
void CRSC_Scene::Loop(void (*callback)())
{
    callback();
}

// Закрытие сцены
void CRSC_Scene::Destroy(void (*callback)())
{
    callback();
}

// ------------------------ Объект игровой сцены        -------------------------- //

// ------------------------ Объект игрового движка      -------------------------- //
CRSC_Engine::CRSC_Engine()
{
    window = NULL;                  // Контекст окна
    render = NULL;                  // Контекст рендера
    countScene = 0;
    scenes = new CRSC_Scene[countScene];
};

CRSC_Engine::~CRSC_Engine()
{
    delete []scenes;
    Mix_CloseAudio();
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
};

// Создает экземпляр Corsac Engine окна
void CRSC_Engine::create(const char* TitleProgram)
{

    // SDL
    !SDL_Init(SDL_INIT_EVERYTHING);

    // MIX
    !Mix_Init(MIX_INIT_MP3);

    // IMG
    IMG_Init(IMG_INIT_PNG);

    // Config
    config.init();

    // Window
    window = SDL_CreateWindow(
        TitleProgram,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        config.screenWidth,
        config.screenHeight,
        SDL_WINDOW_SHOWN
    );

    // FLAGS
    SDL_RendererFlags flags = SDL_RENDERER_ACCELERATED;
    if (config.presentvsync) {
        flags = SDL_RENDERER_PRESENTVSYNC, SDL_RENDERER_ACCELERATED;
    }

    // Render
    render = SDL_CreateRenderer(
        window,
        -1,
        flags
    );

    // Устанавливаем настройки из конфига
    setStartSettings();

    // Настраиваем качество звука
    !Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
};

CRSC_Scene CRSC_Engine::CreateScene(
    void (*callbackLoading)(),
    void (*callbackLoop)(),
    void (*callbackDestroy)()
) {
    countScene++;
    scenes[countScene] = CRSC_Scene(callbackLoading, callbackLoop, callbackDestroy);
    return scenes[countScene];
}

// Устанавливаем настройки из конфига
void CRSC_Engine::setStartSettings()
{
    if (config.fullScreen) {
        SDL_SetWindowBordered(window, SDL_FALSE);
        SDL_SetWindowFullscreen(window, 0);
        SDL_SetWindowGrab(window, SDL_TRUE);
    }
    SDL_SetWindowBrightness(window, config.brigh);
};

// Конструктор
CRSC_Engine CRSC_EngineCreate(const char* TitleProgram)
{
    CRSC_Engine engine;
    engine.create(TitleProgram);
    return engine;
};
// ------------------------ Объект игрового движка      -------------------------- //