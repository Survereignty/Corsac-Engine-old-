#include "./bin/CRSC/CRSC.h"

CRSC_Engine Engine = CRSC_Init("CG", "Corsac");

CRSC_Scene Scene = Engine.CreateScene("Scene");

void Loading()
{

}

void Event()
{

}

void Loop()
{

}

void Destroy()
{

}

int main(int argc, char const *argv[])
{
    Scene.Methods(Loading, Event, Loop, Destroy);
    Scene.Play();
    return 0;
};