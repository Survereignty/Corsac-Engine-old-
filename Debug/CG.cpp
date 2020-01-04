#include "./bin/CRSC/CRSC.h"

#include "./bin/Rily/rily.h"

CRSC_Engine Engine = CRSC_Init("CG", "Corsac");
SDL_Renderer* R = Engine.getRenderer();
Rily r(R);

CRSC_Img* img = Engine.getImg();

class Menu : public CRSC_Scene
{
private:
    Rect *obj, *obj2;
    void Loading()
    {
        obj   = r.CreateRect("1", 0, 0, Engine.Video.screenWidth, Engine.Video.screenHeight, 0, 0, 0, 255); 
        obj2  = r.CreateRect("1", 100, 100, 50, 50, 100, 100, 100, 255);
        
        auto On = [this]()
        {
            if(this->obj2->r<200) this->obj2->r+=10;
            if(this->obj2->g<150) this->obj2->g+=20;
            if(this->obj2->b>30)  this->obj2->b-=15;
        };

        auto ClickD = [this]()
        {
            obj2->Color(0, 0, 0);
        };

        auto ClickU = [this]()
        {
            obj2->Color(100, 100, 100);
        };

        r.UpClick(obj2, ClickU);
        r.OnMouse(obj2, On);
        r.DownClick(obj2, ClickD);
    };

    void Events()
    {
        r.ChekEvent(e);
    }

    void Loop()
    {
        r.DrawingObjects();
    }

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