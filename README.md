# Corsac 2D Game Engine

* Основан на SDL2 2.0.10(stable)

# Необходимые зависимости

```bash
sudo apt install libsdl2{,-image,-mixer,-ttf,-gfx}-dev

```

# Documentation

Для инициализации окна и поверхности рисования, следует вызвать функцию CRSC_EngineCreate, и передать два аргумента,
"наименование приложения(const char*)" и "настроики по умолчанию(CRSC_Settings*)":
```c++
CRSC_Engine Engine = CRSC_EngineCreate("TestGame", DefaultSettings);
```

Полученный объект содержить свойства:
```c++
Engine.window;  // Окно приложения        SDL_Window*
Engine.render;  // Поверхность рисования  SDL_Renderer*
Engine.path;    // Путь до папки с игрой  char*

Engine.config;              // Конфигурация                 CRSC_Config
Engine.config.settings;     // Пользовательские настройки   CRSC_Settings*
```

Настройки по умолчанию:
*обязательно должен являться ссылкой.
```c++
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
```

Для создания сцену нужно вызвать метод CreateScene() у раннее инициализованого движка и передать аргумент "название сцены":
```c++
CRSC_Scene NewScene = Engine.CreateScene("NewScene");
```

Теперь можно передать сцене методы:
*устанавливаем функции: Загрузки, Событий, Действий, Удаления
```c++
NewScene.Methods(Load, Events, Loop, Destroy);
```

Методы управления сценой:
```c++
// Запускает сцену
NewScene.Play();
// Останавливает сцену
NewScene.Stop();
```

Пример работы SDL потоков:
```c++
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
```

# Makefile

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