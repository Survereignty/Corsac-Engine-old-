#include "./bin/CRSC/CRSC.h"

CRSC_Engine Engine = CRSC_EngineCreate("Corsac Game");

int main(int argc, char const *argv[])
{
    SDL_Delay(2000);
    CRSC_Scene scene = CRSC_SceneCreate(NULL, NULL, NULL);

    std::cout << "hi" << std::endl;
    return 0;
}
