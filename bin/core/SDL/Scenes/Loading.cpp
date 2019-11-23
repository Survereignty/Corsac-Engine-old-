class Loading : private Scene
{
public:
    Loading() {
        state   = 1;
        next    = 1;
    };

    ~ Loading() {

    };

    int start() {
        Load();
        Draw();
        while (state != 0)
        {
            Input();
            Update();
        }
        return next;
    }
    int stop() {
        state = 0;
    }
private:

    void Load() {

    }

    void Draw() {

    }

    void Update() {

    }

    void Input() {
        SDL_Event evnt;
        while (SDL_PollEvent(&evnt)) {
            switch (evnt.type)
            {
            case SDL_QUIT:
                state = 0;
                next = 0;
                break;
            }
        }
    }
};