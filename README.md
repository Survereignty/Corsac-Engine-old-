# Corsac 2D Game Engine

* Основан на SDL2 2.0.10(stable)

# Необходимые зависимости

```bash
sudo apt install libsdl2{,-image,-mixer,-ttf,-gfx}-dev

```

# Функции и методы CRSC

```c++

// Создаем объект настроек по умолчанию и ссылку на него
CRSC_Settings* DefaultSettings = new CRSC_Settings(
    // [Video]
    800,    // Ширина экрана
    600,    // Высота экрана
    0,      // Полноэкранный режим:         0-выкл. 1-вкл.
    0,      // Вертикальная синхронизация:  0-выкл. 1-вкл.
    0,      // Ограничения по фпс:          0-выкл. 1-вкл.
    30,     // На какое число ограничить
    1.0,    // Цветовая гамма
    // [Audio]
    75,     // Общая громкость:             0 - 100
    75,     // Громкость музыки:            0 - 100
    75      // Громкость звуков:            0 - 100
);

// Инициализация игрового окна и соответсвующих настроек
CRSC_Engine Engine = CRSC_EngineCreate("TestGame", DefaultSettings);

// Инициализация сцены
CRSC_Scene NewScene = Engine.CreateScene("NewScene");

// Устанавливаем функции: Загрузки, Событий, Действий, Удаления
NewScene.Methods(Load, Events, Loop, Destroy);

// Запускает сцену
NewScene.Play();

// Останавливает сцену
NewScene.Stop();

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

```Makefile
# Компилятор
CC = g++

# Название игры
GAME = TestGame

# Зависимости
LIBS = -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

# Debug
DSOURCES = ./Debug/bin/CRSC.cpp  ./Debug/bin/CRSC_lib.cpp

.PHONY: debug
debug:
	$(CC) -lm ./Debug/main.cpp $(DSOURCES) $(LIBS) -o ./Debug/$(GAME)
	./Debug/$(GAME)

.DEFAULT_GOAL := debug

```