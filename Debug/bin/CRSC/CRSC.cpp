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

// Объект
void CRSC_Object::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod(tex, red, green, blue);
}
void CRSC_Object::setAlpha(Uint8 alpha)
{
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(tex, alpha);
}
CRSC_Object::CRSC_Object(SDL_Rect* rect, SDL_Texture* tex)
{
    this->rect = rect;
    this->tex = tex;
}
CRSC_Object::~CRSC_Object(){}

////////////////////////////////////////////////////////////////////////////////////////////

// Центр управления SDL_IMG
int CRSC_Graph::Init(SDL_Renderer* R, CRSC_Logs* Logs)
{
    if (!(IMG_Init(Flags.flags) & Flags.flags)) return 1;
    if (TTF_Init() == -1) return 1;
    this->R = R;
    this->Logs = Logs;
    return 0;
};
void CRSC_Graph::DrawingObjects()
{
    for (CRSC_Object* item : this->texs)
    {
        SDL_RenderCopyEx(R, item->tex, NULL, item->rect, item->angle, item->center, item->flip);
    }
    SDL_RenderPresent(R);
};
void CRSC_Graph::DestroyObjects()
{
    SDL_SetRenderDrawColor(R, 0, 0, 0, 255);
    SDL_RenderClear(R);
    for (CRSC_Object* item : this->texs)
    {
        SDL_DestroyTexture(item->tex);
        delete item;
    }
    this->texs.clear();
};
CRSC_Object* CRSC_Graph::CreateObject(std::string p, int x, int y, int w, int h, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Texture* n = NULL;
    std::string path = Flags.pathToSprite + p + Flags.format;
    SDL_Surface* l = IMG_Load(path.c_str());
    if(l == NULL) Logs->Set("Unable to load image! SDL_image Error: ", path + " " + IMG_GetError());
    SDL_SetColorKey(l, SDL_TRUE, SDL_MapRGB( l->format, 0, 0xFF, 0xFF));
    n = SDL_CreateTextureFromSurface(R, l);
    SDL_FreeSurface(l);
    SDL_Rect* r = new SDL_Rect();
        r->x = x; r->y = y;
        r->w = w; r->h = h;
    CRSC_Object* obj = new CRSC_Object(r, n);
    obj->angle = angle; obj->center = center; obj->flip = flip;
    this->texs.push_back(obj);
    return obj;
}
CRSC_Graph::CRSC_Graph(){};
CRSC_Graph::~CRSC_Graph()
{
    TTF_Quit();
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
    //setAutoSizes();
    if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )) Logs.Set("Warning: Linear texture filtering not enabled!", "");
    if (Sdl.CreateWindow(Info.GameName,
        Video.Width,
        Video.Height
    )) Logs.Set("Window could not be created! SDL Error: ", SDL_GetError());
    setFull(false);
    if (Sdl.CreateRenderer()) Logs.Set("Renderer could not be created! SDL Error: ", SDL_GetError());
    if (Graph.Init(Sdl.Renderer, &Logs)) Logs.Set("SDL_image could not initialize! SDL_image Error: ", SDL_GetError());
    SDL_SetRenderDrawColor(Sdl.Renderer, 0, 0, 0, 255);
    SDL_RenderClear(Sdl.Renderer);
    if (Mix.Init()) Logs.Set("SDL_mix could not initialize! SDL_Error: ", SDL_GetError());
};
CRSC_Graph* CRSC_Engine::getGraph()
{
    return &Graph;
};
SDL_Renderer* CRSC_Engine::getRenderer()
{
    return Sdl.Renderer;
};
void CRSC_Engine::setAutoSizes()
{
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
        Video.Width = dm.w;
        Video.Height = dm.h;
}
void CRSC_Engine::setFull(bool permanently)
{
    if (Video.Full || permanently) Video.Full = true; SDL_SetWindowFullscreen(Sdl.Window, 0);
}
CRSC_Engine CRSC_Init(const char* GameName, const char* OrgName)
{
    CRSC_Engine E(GameName, OrgName);
    return E;
};

////////////////////////////////////////////////////////////////////////////////////////////
