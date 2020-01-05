#include "./bin/CRSC/CRSC.h"

#include "./bin/Rily/rily.h"

CRSC_Engine E = CRSC_Init("CG", "Corsac");
SDL_Renderer* r = E.getRenderer();
CRSC_Graph* g = E.getGraph();
Rily ri(r);

class Menu : public CRSC_Scene
{
private:
    CRSC_Texture* background;
    CRSC_Texture* foo;

    CRSC_Timer timer;

    Rect* back;

    std::stringstream timeText;
    int frame = 0;
    void Loading()
    {
        //background = g->CreateObject("background", 0, 0);
        back = ri.CreateRect("bg", 0, 0, 1200, 800, 0, 100, 200);

        foo = g->CreateObject("foo", 100, 50);

        // timer.start();
        // timeText.str( "" );
        // timeText << "Seconds since start time " << (timer.getTicks() / 1000.f);
        // text = g->CreateText(timeText.str().c_str(), 255, 0, 0, 0, 0);
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
        if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_W]) foo->rect->y -= 10;
        if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_S]) foo->rect->y += 10;
        if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_A]) {
            foo->rect->x -= 10;
            foo->flip = SDL_FLIP_NONE;
        }
        if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_D]) {
            foo->rect->x += 10;
            foo->flip = SDL_FLIP_HORIZONTAL;
        }

        ri.DrawingObjects();
        g->DrawingObjects();

        SDL_Delay(1);
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