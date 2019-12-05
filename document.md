# Необходимые зависимости

```bash
sudo apt install libsdl2{,-image,-mixer,-ttf,-gfx}-dev

```

# Функции и методы CRSC

```c++

// Инициализация игрового окна и соответсвующих настроек
CRSC_Engine engine = CRSC_EngineCreate("SkyFort");

// Инициализация сцены, передайте функцию загрузки, цикла и закрытия
CRSC_Scene scene = CRSC_SceneCreate(Load, Loop, Destroy);

// Запускает сцену
scene.Play();

// Останавливает сцену
scene.Stop();

// ----- Потоки --------
// Создаем поток передавая функцию, тег, данные
SDL_Thread* MyTread = SDL_CreateThread( threadFunction, "MyTread", (void*)data);

// Пример функции для потока
int threadFunction( void* data )
{
    printf( "Running thread with value = %d\n", (int)data );
    return 0;
}

// Ожидание окончания потока
SDL_WaitThread( MyTread, NULL );
// ----- Потоки --------

```