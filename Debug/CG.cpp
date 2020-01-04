#include "./bin/CRSC/CRSC.h"

CRSC_Engine Engine = CRSC_Init("CG", "Corsac");

CRSC_Img* img = Engine.getImg();

class Menu : public CRSC_Scene
{
private:
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