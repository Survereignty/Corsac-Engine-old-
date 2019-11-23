#include <iostream>

#include "SDL/SDL.cpp"
#include "SDL/Scenes/Menu.cpp"

class Game
{
public:
    void run() {
        init();
        gaming();
    };
private:
    int  state = 1;
    SDL  engine;
        Menu menu;

    void init() {
        engine.init("Corsac engine");
    };

    void gaming() {
        while(state != 0) {
            if (state = 1) {
                state = menu.start(engine);
            }
        }
    };
};
