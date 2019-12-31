#include "CRSC.h"

////////////////////////////////////////////////////////////////////////////
// Пользовательские настройки игры
CRSC_Settings::CRSC_Settings()
{
    Video       = NULL;
    Audio       = NULL;
    Gameplay    = NULL;
    Keys        = NULL;
};
CRSC_Settings::CRSC_Settings(
        CRSC_Video*     Video,
        CRSC_Audio*     Audio,
        CRSC_Gameplay*  Gameplay,
        CRSC_Keys*      Keys
) {
    this->Video       = Video;
    this->Audio       = Audio;
    this->Gameplay    = Gameplay;
    this->Keys        = Keys;
};
CRSC_Settings::~CRSC_Settings()
{
    _path       = NULL;

    Video       = NULL;
    Audio       = NULL;
    Gameplay    = NULL;
    Keys        = NULL;
};
int CRSC_Settings::Save() {
    std::ofstream s;
    s.open(_path);
    if (!s.is_open()) {
        s.close();
        return 0;
    }
    CRSC_SaveSettings S{
        *this->Video,
        *this->Audio,
        *this->Gameplay,
        *this->Keys
    };
    s.write((char*)&S, sizeof(CRSC_SaveSettings));
    s.close();
    return 1;
}
int CRSC_Settings::Set() {
    std::ifstream s;
    s.open(_path);
    if (!s.is_open()) {
        s.close();
        return 0;
    }
    CRSC_SaveSettings S;
    s.read((char*)&S, sizeof(CRSC_SaveSettings));
    *this->Video = S.V;
    *this->Audio = S.A;
    *this->Gameplay = S.G;
    *this->Keys = S.K;
    s.close();
    return 1;
}
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Логирование
CRSC_Log::CRSC_Log(CRSC_LogsFlags* LogsFlags)
{
    this->LogsFlags = LogsFlags;
    this->LogsFlags->PATH = strcat(SDL_GetBasePath(), LogsFlags->PATH);
};
CRSC_Log::~CRSC_Log()
{
    LogsFlags = NULL;
};
void CRSC_Log::Error(std::string info, std::string error)
{
    if (LogsFlags->USE_GAME)     Logs.insert(make_pair("[ERROR] ", info + error));
    if (LogsFlags->USE_TERMINAL) std::cout << "[ERROR] " << info << error << std::endl;
    if (LogsFlags->USE_FILE)     CRSC_CreateAndWrite(this->LogsFlags->PATH, "[ERROR] " + info + error);
};
void CRSC_Log::Info(std::string info)
{
    if (LogsFlags->USE_GAME)     Logs.insert(make_pair("[INFO] ", info));
    if (LogsFlags->USE_TERMINAL) std::cout << "[INFO] " << info << std::endl;
    if (LogsFlags->USE_FILE)     CRSC_CreateAndWrite(this->LogsFlags->PATH, "[INFO] " + info);
};
void CRSC_Log::Crash(std::string info, std::string error)
{
    if (LogsFlags->USE_GAME)     Logs.insert(make_pair("[CRASH] ", info + error));
    if (LogsFlags->USE_TERMINAL) std::cout << "[CRASH] " << info << error << std::endl;
    if (LogsFlags->USE_FILE)     CRSC_CreateAndWrite(this->LogsFlags->PATH, "[CRASH] " + info + error);
    exit(0);
};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Корневые настройки игры
CRSC_Config::CRSC_Config(
    const char*         GameName,           // Название игры
    const char*         OrganizationName,   // Название организации
    CRSC_Settings*      Settings,           // Пользовательские настройки игры
    CRSC_ConfigFlags*   ConfigFlags,        // Флаги для CRSC
    CRSC_Log*           Log                 // Логирование
) {
    this->Settings          = Settings;
    this->OrganizationName  = OrganizationName;
    this->GameName          = GameName;
    this->ConfigFlags       = ConfigFlags;
    this->Log               = Log;

    GamePath = SDL_GetBasePath();
    UserPath = SDL_GetPrefPath(OrganizationName, GameName);
};
CRSC_Config::~CRSC_Config()
{
    Log         = NULL;
    ConfigFlags = NULL;
    fpsScreen   = 0;
    Settings    = NULL;
};
void CRSC_Config::FindAndSetRecommendedSettings()
{
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
        Settings->Video->screenWidth = dm.w;
        Settings->Video->screenHeight = dm.h;
        fpsScreen = dm.refresh_rate;
};
void CRSC_Config::UseDefProfile()
{
    Settings->_path = strcat(UserPath, "defusf.crsc");
    if (CRSC_CheckFile(Settings->_path)) {
        if ((ConfigFlags->CRSC_READ_SETTINGS) && (!Settings->Set()))  Log->Error("Settings is not set: ", Settings->_path);
    } else {
        if (ConfigFlags->CRSC_AUTO_SETTINGS_FIRST_SETUP) FindAndSetRecommendedSettings();
        if ((ConfigFlags->CRSC_SAVE_SETTINGS) && (!Settings->Save())) Log->Error("Settings is not save: ", Settings->_path);
    }
}
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Настройки Img
CRSC_Img::CRSC_Img
    (
        CRSC_Config*    Config,     // Корневые настройки игры
        IMG_InitFlags   ImgFlags    // Флаги для SDL_IMG
    ) {
        this->ImgFlags = ImgFlags;
        this->Config    = Config;    // Корневые настройки игры
    };
CRSC_Img::~CRSC_Img()
{
    Config = NULL;
    IMG_Quit();
};
int CRSC_Img::_init()
{
    if (!(IMG_Init(ImgFlags) & ImgFlags)) Config->Log->Crash("SDL_image could not initialize! SDL_image Error: ", IMG_GetError());
};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Настройки Ttf
CRSC_Ttf::CRSC_Ttf
    (
        CRSC_Config*    Config      // Корневые настройки игры
    ) {
        this->Config    = Config;    // Корневые настройки игры
    };
CRSC_Ttf::~CRSC_Ttf()
{
    Config = NULL;
    TTF_Quit();
};
int CRSC_Ttf::_init()
{
    if (TTF_Init() == -1) Config->Log->Crash("SDL_ttf could not initialize! SDL_ttf Error: ", TTF_GetError());
};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Настройки Mix
CRSC_Mix::CRSC_Mix
    (
        CRSC_Config*    Config,     // Корневые настройки игры
        MIX_InitFlags   MixFlags,
        int frequency,
        Uint16 format,
        int channels,
        int chunksize
    ) {
        this->Config    = Config;    // Корневые настройки игры
        this->MixFlags  = MixFlags;
        this->frequency = frequency;
        this->format    = format;
        this->channels  = channels;
        this->chunksize = chunksize;
    };
CRSC_Mix::~CRSC_Mix()
{
    frequency = 0;
    format    = 0;
    channels  = 0;
    chunksize = 0;
    Config = NULL;
    Mix_CloseAudio();
    Mix_Quit();
};
int CRSC_Mix::_init()
{
    if (Mix_Init(MixFlags)) Config->Log->Crash("SDL_mix could not initialize! SDL_Error: ", Mix_GetError());
};
void CRSC_Mix::SetSounds()
{
    Mix_OpenAudio(frequency, format, channels, chunksize);
};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Настройки SDL2
CRSC_SDL::CRSC_SDL
    (
        CRSC_Config*        Config,     // Корневые настройки игры
        unsigned int        SdlFlags,   // Флаги для SDL2
        SDL_WindowFlags     WinFlags,   // Флаги для Окна
        SDL_RendererFlags   RenFlags    // Флаги для контекста рендера
    ) {
        this->Config   = Config;    // Корневые настройки игры
        this->SdlFlags = SdlFlags;  // Флаги для SDL2
        this->WinFlags = WinFlags;  // Флаги для Окна
        this->RenFlags = RenFlags;  // Флаги для контекста рендера
    };
CRSC_SDL::~CRSC_SDL()
{
    Config = NULL;
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    Renderer    = NULL;
    Window      = NULL;
    SDL_Quit();
};
void CRSC_SDL::_init()
{
    if (SDL_Init(SdlFlags)) Config->Log->Crash("SDL could not initialize! SDL_Error: ", SDL_GetError());
}
void CRSC_SDL::_createWindow()
{
    Config->UseDefProfile();

    Window = SDL_CreateWindow(
        Config->GameName,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        Config->Settings->Video->screenWidth,
        Config->Settings->Video->screenHeight,
        WinFlags
    );
    if (Window == NULL) Config->Log->Crash("Window could not be created! SDL Error: ", SDL_GetError());
};
void CRSC_SDL::_createRenderer()
{
    if (Config->Settings->Video->presentvsync) {
        RenFlags = SDL_RENDERER_PRESENTVSYNC, SDL_RENDERER_ACCELERATED;
    }

    Renderer = SDL_CreateRenderer(
        Window,
        -1,
        RenFlags
    );
    if (Renderer == NULL) Config->Log->Crash("Renderer could not be created! SDL Error: ", SDL_GetError());

    if (Config->Settings->Video->fullScreen) {
        SDL_SetWindowBordered(Window, SDL_FALSE);
        SDL_SetWindowFullscreen(Window, 0);
        SDL_SetWindowGrab(Window, SDL_TRUE);
    }
    SDL_SetWindowBrightness(Window, Config->Settings->Video->brigh);
};
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Игровой движек
CRSC_Engine::CRSC_Engine(
        CRSC_SDL* SDL,
        CRSC_Mix* Mix,
        CRSC_Img* Img,
        CRSC_Ttf* Ttf
) {
    this->SDL = SDL;
    this->Mix = Mix;
    this->Img = Img;
    this->Ttf = Ttf;
};
CRSC_Engine::~CRSC_Engine()
{
    Mix = NULL;
    Img = NULL;
    Ttf = NULL;
    SDL = NULL;
};
int CRSC_Engine::Setup()
{
    SDL->_init();
    Img->_init();
    Mix->_init();
    Mix->SetSounds();
    Ttf->_init();
    SDL->_createWindow();
    SDL->_createRenderer();
}
////////////////////////////////////////////////////////////////////////////