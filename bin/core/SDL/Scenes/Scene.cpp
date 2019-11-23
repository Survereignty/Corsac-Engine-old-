#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

class Scene {
    public:
        int state;
        int next;
        SDL engine;
};
