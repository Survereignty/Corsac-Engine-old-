#include "./bin/CRSC/CRSC.h"

CRSC_Engine Engine = CRSC_Init("CG", "Corsac");

class Menu : public CRSC_Scene
{
private:

public:
    Menu(SDL_Renderer* Renderer)
    {
        this->Renderer = Renderer;
    };
    ~Menu(){};
    void Loading()
    {

    };
    void Events()
    {

    };
    void Loop()
    {

    };
    void Destroy()
    {

    }
};


int main(int argc, char const *argv[])
{
    SDL_Renderer* R = Engine.getRenderer();
    Menu menu(R);

    menu.Play();

    return 0;
};