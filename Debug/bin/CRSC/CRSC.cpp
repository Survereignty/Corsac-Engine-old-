#include "CRSC.h"

// Создать файл и записать туда строку
std::ofstream CRSC_CreateAndWrite(const char* path, std::string elem) {
    std::ofstream file;
    file.open(path, std::ofstream::app);
    file << elem << std::endl;
    file.close();
    return file;
}

////////////////////////////////////////////////////////////////////////////////////////////

// Центр хранения и управления логами
void CRSC_Logs::Set(std::string info, std::string error)
{
    Logs.insert(make_pair("[ERROR] ", info + error));
    if (flags.USE_TERMINAL) std::cout << "[ERROR] " << info << error << std::endl;
    if (flags.USE_FILE) CRSC_CreateAndWrite(this->flags.PATH, "[ERROR] " + info + error);
};
CRSC_Logs::CRSC_Logs(){};
CRSC_Logs::~CRSC_Logs(){};

////////////////////////////////////////////////////////////////////////////////////////////

// Центр управления SDL2
int CRSC_Sdl::Init()
{
    if (SDL_Init(SdlFlags)) return 1;
    return 0;
};
int CRSC_Sdl::CreateWindow(
    const char* GameName,
    int & Width,
    int & Height
) {
    Window = SDL_CreateWindow(
        GameName,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        Width,
        Height,
        WinFlags
    );
    if (Window == NULL) return 1;
    return 0;
};
int CRSC_Sdl::CreateRenderer()
{
    Renderer = SDL_CreateRenderer(
        Window,
        -1,
        RenFlags
    );
    if (Renderer == NULL) return 1;
    return 0;
};
CRSC_Sdl::CRSC_Sdl()
{
    SdlFlags = SDL_INIT_EVERYTHING;
    WinFlags = SDL_WINDOW_SHOWN;
    RenFlags = SDL_RENDERER_ACCELERATED, SDL_RENDERER_PRESENTVSYNC;
};
CRSC_Sdl::~CRSC_Sdl()
{
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
};

////////////////////////////////////////////////////////////////////////////////////////////

// Центр управления SDL_IMG
int CRSC_Img::Init()
{
    if (!(IMG_Init(ImgFlags) & ImgFlags)) return 1;
    return 0;
};
CRSC_Img::CRSC_Img()
{
    ImgFlags = IMG_INIT_PNG;
};
CRSC_Img::~CRSC_Img()
{
    IMG_Quit();
};

////////////////////////////////////////////////////////////////////////////////////////////

// Центр управления SDL_MIX
int CRSC_Mix::Init()
{
    if (Mix_Init(Format.flags)) return 1;
    Mix_OpenAudio(Format.frequency, Format.format, Format.channels, Format.chunksize);
    return 0;
};
CRSC_Mix::CRSC_Mix(){};
CRSC_Mix::~CRSC_Mix()
{
    Mix_CloseAudio();
    Mix_Quit();
};

////////////////////////////////////////////////////////////////////////////////////////////

// Центр управления SDL_Ttf
int CRSC_Ttf::Init()
{
    if (TTF_Init() == -1) return 1;
    return 0;
};
CRSC_Ttf::CRSC_Ttf(){};
CRSC_Ttf::~CRSC_Ttf()
{
    TTF_Quit();
};

////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////

// Центр управления
CRSC_Engine::CRSC_Engine(const char* GameName, const char* OrgName)
{
    Info.GameName = GameName;
    Info.OrgName = OrgName;
    Info.GamePath = SDL_GetBasePath();
    Info.UserPath = SDL_GetPrefPath(OrgName, GameName);

    Setup();
};
CRSC_Engine::~CRSC_Engine(){};
void CRSC_Engine::Setup()
{
    // Запуск всех модулей
    if (Sdl.Init()) Logs.Set("SDL could not initialize! SDL_Error: ", SDL_GetError());
    if (Img.Init()) Logs.Set("SDL_image could not initialize! SDL_image Error: ", SDL_GetError());
    if (Mix.Init()) Logs.Set("SDL_mix could not initialize! SDL_Error: ", SDL_GetError());
    if (Ttf.Init()) Logs.Set("SDL_ttf could not initialize! SDL_ttf Error: ", SDL_GetError());
    //setAutoSizes();
    if (Sdl.CreateWindow(Info.GameName,
        Video.screenWidth,
        Video.screenHeight
    )) Logs.Set("Window could not be created! SDL Error: ", SDL_GetError());
    setFullScreen(false);
    if (Sdl.CreateRenderer()) Logs.Set("Renderer could not be created! SDL Error: ", SDL_GetError());
};
CRSC_Scene CRSC_Engine::CreateScene(std::string name) {
    CRSC_Scene scene(name, Sdl.Renderer);
    return scene;
}
void CRSC_Engine::setAutoSizes()
{
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
        Video.screenWidth = dm.w;
        Video.screenHeight = dm.h;
}
void CRSC_Engine::setFullScreen(bool permanently)
{
    if (Video.fullScreen || permanently) Video.fullScreen = true; SDL_SetWindowFullscreen(Sdl.Window, 0);
}
CRSC_Engine CRSC_Init(const char* GameName, const char* OrgName)
{
    CRSC_Engine E(GameName, OrgName);
    return E;
};

////////////////////////////////////////////////////////////////////////////////////////////
