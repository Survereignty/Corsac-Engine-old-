#include "./bin/CRSC/CRSC.h"

//#include "./bin/Rily/rily.h"

CRSC_Engine E = CRSC_Init("CG", "Corsac");
SDL_Renderer* r = E.getRenderer();
CRSC_Graph* g = E.getGraph();
//Rily r(R);

class Menu : public CRSC_Scene
{
private:
    CRSC_Object* background;
    CRSC_Object* foo;

    void Loading()
    {
        background = g->CreateObject("background", 0, 0, E.Video.Width, E.Video.Height);
        foo = g->CreateObject("foo", 240, 190, 170, 300);

        background->setColor(0, 0, 100);
        foo->setAlpha(200);
    };

    void Events()
    {
        switch (e.type) {
            case SDL_QUIT:
                Stop();
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        Stop();
                        break;
                    default:
                        break;
                }
            case SDL_KEYUP:
                break;
            default: break;
        }
    }

    void Loop()
    {
        if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_W]) foo->rect->y -= 1;
        if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_S]) foo->rect->y += 1;
        if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_A]) {
            foo->rect->x -= 1;
            foo->flip = SDL_FLIP_NONE;
        }
        if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_D]) {
            foo->rect->x += 1;
            foo->flip = SDL_FLIP_HORIZONTAL;
        }
        g->DrawingObjects();
        SDL_Delay(3);
    }

    void Destroy()
    {
        g->DestroyObjects();
    }
public:
    Menu(){};
    ~Menu(){};
};

int main(int argc, char const *argv[])
{
    Menu menu;

    menu.Play();

    return 0;
};