#include "Scene.cpp"

#include "Loading.cpp"

class  Menu : private Scene
{
public:
    Menu() {
        state   = 1;
        next    = 1;
    };
    ~ Menu() {
    };

    int start(SDL s) {
        engine = s;
        Load();
        Draw();
        while (state != 0)
        {
            Input();
            Update();
        }
        return next;
    }
private:
    Loading loading;

    void Load() {
        // int loadEnd = loading.start();
        // if (loadEnd == 0) {
        //     next = 0;
        //     state = 0;
        // }
        //"../../../data/sprite/player.bmp
        //"./bin/data/sprite/player.bmp
        SDL_Surface *bmp = SDL_LoadBMP("./bin/data/sprite/player.bmp");
        if (bmp == nullptr){
            std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        }
        SDL_Texture *tex = SDL_CreateTextureFromSurface(engine.render, bmp);
        SDL_FreeSurface(bmp);
        if (tex == nullptr){
            std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        }

        SDL_RenderClear(engine.render);
        SDL_RenderCopy(engine.render, tex, NULL, NULL);
        SDL_RenderPresent(engine.render);

        //loading.stop();
    }

    void Draw() {

    }

    void Update() {
    }

    void Input() {
        SDL_Event evnt;
        while (SDL_PollEvent(&evnt)) {
            switch (evnt.type)
            {
                // Выход из игры
            case SDL_QUIT:
                state = 0;
                next = 0;
                break;
                // Позиция мыши
            case SDL_MOUSEMOTION:
                // std::cout
                //     << evnt.motion.x
                //     << " "
                //     << evnt.motion.y
                // << std::endl;
                break;
            }
        }
    };
};