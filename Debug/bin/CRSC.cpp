#include "CRSC.h"

// ------------------------ Объект настроек проиложения -------------------------- //
CRSC_Config::CRSC_Config()
{

};

CRSC_Config::~CRSC_Config()
{
    std::cout << "Config is close" << std::endl;
};

// Инициализация Создаем/читаем файл
void CRSC_Config::init(char* pathMain, CRSC_Settings* set)
{

    settings = set;

    // Путь до config.ini
    path = strcat(pathMain, "Config.ini");

    std::map <std::string, std::string> data;

    if (CRSC_CheckIni(path)) {
        setDefault();

        std::vector<std::string> setSettings = {
        "[Video]",
            "screenWidth="      + std::to_string(settings->screenWidth),
            "screenHeight="     + std::to_string(settings->screenHeight),
            "fullScreen="       + std::to_string(settings->fullScreen),
            "presentvsync="     + std::to_string(settings->presentvsync),
            "fpsOut="           + std::to_string(settings->fpsOut),
            "maxFps="           + std::to_string(settings->maxFps),
            "brigh="            + std::to_string(settings->brigh),
        "[Audio]",
            "generalValume="    + std::to_string(settings->generalValume),
            "musicValume="      + std::to_string(settings->musicValume),
            "soundsValume="     + std::to_string(settings->soundsValume)
        };

        CRSC_CreateAndWrite(path, setSettings);
    }

    data = CRSC_ReadIni(path);

    settings->screenWidth     = stoi(data["screenWidth"]);
    settings->screenHeight    = stoi(data["screenHeight"]);
    settings->fullScreen      = stoi(data["fullScreen"]);
    settings->presentvsync    = stoi(data["presentvsync"]);
    settings->fpsOut          = stoi(data["fpsOut"]);
    settings->maxFps          = stoi(data["maxFps"]);
    settings->brigh           = stoi(data["brigh"]);
    settings->generalValume   = stoi(data["generalValume"]);
    settings->musicValume     = stoi(data["musicValume"]);
    settings->soundsValume    = stoi(data["soundsValume"]);
};

// Устанавливаем текущие параметры экрана пользователя
void CRSC_Config::setDefault()
{
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
        settings->screenWidth = dm.w;
        settings->screenHeight = dm.h;
        fpsScreen = dm.refresh_rate;
};
// ------------------------ Объект настроек проиложения -------------------------- //

// ------------------------ Объект игровой сцены        -------------------------- //
CRSC_Scene::CRSC_Scene(
    std::string     name,
    SDL_Renderer*   render
) {
    cbload  = NULL;
    cbloop  = NULL;
    cbdest  = NULL;
    cbevent = NULL;

    this->name = name;
    this->render = render;
};

void CRSC_Scene::Methods(
    void (*callbackLoading)(),
    void (*callbackEvent)(),
    void (*callbackLoop)(),
    void (*callbackDestroy)()
) {
    cbload  = callbackLoading;
    cbevent = callbackEvent;
    cbloop  = callbackLoop;
    cbdest  = callbackDestroy;
}

CRSC_Scene::CRSC_Scene() {
    cbload  = NULL;
    cbevent = NULL;
    cbloop  = NULL;
    cbdest  = NULL;
    render  = NULL;
};

CRSC_Scene::~CRSC_Scene()
{
    std::cout << "Scene (" << name << ") is close" << std::endl;
};

// Запустить сцену
void CRSC_Scene::Play()
{
    state = 1;
    Loading(cbload);
    while (state != 0)
    {
        Events(cbevent);
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

// Цикл событий
void CRSC_Scene::Events(void (*callback)())
{
    while (SDL_PollEvent(&e) != 0) {
        if( e.type == SDL_QUIT )
        {
            Stop();
        }
        callback();
    }
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
    window  = NULL; // Контекст окна
    render  = NULL; // Контекст рендера
    font    = NULL; // Шрифт

    path    = SDL_GetBasePath(); // Путь до приложения
};

CRSC_Engine::~CRSC_Engine()
{
    Mix_CloseAudio();
    // TTF_CloseFont(font);
    // font = NULL;
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    render = NULL;
    window = NULL;
    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    std::cout << "Engine is close" << std::endl;
};

// Создает экземпляр Corsac Engine окна
void CRSC_Engine::create(const char* TitleProgram, CRSC_Settings* settings)
{

    // SDL
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    // MIX
    if(Mix_Init(MIX_INIT_MP3))
    {
        printf("Mix could not initialize! SDL_Error: %s\n", Mix_GetError());
    }

    // IMG
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    // TTF
    // if (TTF_Init() == -1)
    // {
    //     printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    // }

    // Config
    config.init(path, settings);

    // Window
    window = SDL_CreateWindow(
        TitleProgram,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        config.settings->screenWidth,
        config.settings->screenHeight,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL)
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
    }

    // FLAGS
    SDL_RendererFlags flags = SDL_RENDERER_ACCELERATED;
    if (config.settings->presentvsync) {
        flags = SDL_RENDERER_PRESENTVSYNC, SDL_RENDERER_ACCELERATED;
    }

    // Render
    render = SDL_CreateRenderer(
        window,
        -1,
        flags
    );
    if( render == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    }

    // Устанавливаем настройки из конфига
    setStartSettings();

    // const char* path = strcat(SDL_GetBasePath(), "data/font/18432.ttf");
    // font = TTF_OpenFont(path, 28);
    // if( font == NULL )
    // {
    //     printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
    // }

    // Настраиваем качество звука
    !Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
};

CRSC_Scene CRSC_Engine::CreateScene(std::string name) {
    CRSC_Scene scene = CRSC_Scene(name, render);
    return scene;
}

// Устанавливаем настройки из конфига
void CRSC_Engine::setStartSettings()
{
    if (config.settings->fullScreen) {
        SDL_SetWindowBordered(window, SDL_FALSE);
        SDL_SetWindowFullscreen(window, 0);
        SDL_SetWindowGrab(window, SDL_TRUE);
    }
    SDL_SetWindowBrightness(window, config.settings->brigh);
};

// Конструктор
CRSC_Engine CRSC_EngineCreate(const char* TitleProgram, CRSC_Settings* settings)
{
    CRSC_Engine engine;
    engine.create(TitleProgram, settings);
    return engine;
};
// ------------------------ Объект игрового движка      -------------------------- //