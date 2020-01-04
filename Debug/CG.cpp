#include "./bin/CRSC/CRSC.h"

#include "./bin/Rily/rily.h"

CRSC_Engine Engine = CRSC_Init("CG", "Corsac");
SDL_Renderer* R = Engine.getRenderer();
Rily r(R);

CRSC_Img* img = Engine.getImg();

class Menu : public CRSC_Scene
{
private:
    Rect* obj;
    void Loading()
    {
        obj = r.CreateRect("1", 100, 100, 50, 50, 255, 0, 0, 255);
        auto Click = [this]()
        {
            this->obj->Color(0, 255, 0, 255);
        };
        r.DownClick(obj, Click);
    };
    void Events()
    {
        r.ChekEvent(e);
    };
    void Loop()
    {
        r.DrawingObjects();
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