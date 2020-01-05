#include "./bin/CRSC/CRSC.h"

#include "./bin/Rily/rily.h"

CRSC_Engine E = CRSC_Init("CG", "Corsac");
SDL_Renderer* r = E.getRenderer();
CRSC_Graph* g = E.getGraph();
//Rily r(R);

const int    WALKING_ANIMATION_FRAMES = 4;
SDL_Rect     gSpriteClips[WALKING_ANIMATION_FRAMES];
CRSC_Object* gSpriteSheetTexture;

class Menu : public CRSC_Scene
{
private:
    CRSC_Object* background;
    CRSC_Object* foo;
    CRSC_Object* text;
    CRSC_Timer timer;
    std::stringstream timeText;
    int frame = 0;
    void Loading()
    {
        //background = g->CreateObject("background", 0, 0);
        SDL_Rect* currentClip = &gSpriteClips[ frame / 4 ];
        foo = g->CreateObject("foo", ( E.Video.Width - currentClip->w ) / 2,( E.Video.Height - currentClip->h ) / 2, currentClip);
            gSpriteClips[ 0 ].x =   0;
            gSpriteClips[ 0 ].y =   0;
            gSpriteClips[ 0 ].w =  64;
            gSpriteClips[ 0 ].h = 205;

            gSpriteClips[ 1 ].x =  64;
            gSpriteClips[ 1 ].y =   0;
            gSpriteClips[ 1 ].w =  64;
            gSpriteClips[ 1 ].h = 205;

            gSpriteClips[ 2 ].x = 128;
            gSpriteClips[ 2 ].y =   0;
            gSpriteClips[ 2 ].w =  64;
            gSpriteClips[ 2 ].h = 205;

            gSpriteClips[ 3 ].x = 196;
            gSpriteClips[ 3 ].y =   0;
            gSpriteClips[ 3 ].w =  64;
            gSpriteClips[ 3 ].h = 205;

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
        SDL_SetRenderDrawColor( R, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( R );

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

        ++frame;

        if( frame / 4 >= WALKING_ANIMATION_FRAMES )
        {
            frame = 0;
        }

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