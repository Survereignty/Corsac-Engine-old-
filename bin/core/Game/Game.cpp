#include "Game.h"
#include <iostream>
#include <string>

// Обработчик ошибок
void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Нажмите на кнопку чтобы выйти...";
    int tmp;
    std::cin >> tmp;
    SDL_Quit();
}

Game::Game()
{
    _title = "Corsac engine";
    _window = nullptr;
    _screenWidth = 800;
    _screenHeight = 600;
    _gameState = GameState::PLAY;
}

Game::~Game()
{

}

void Game::run() {
    initSystems();

    gameLoop();
}

// Инициализация
void Game::initSystems() {

    // SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Window
    _window = SDL_CreateWindow(
        _title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        _screenWidth,
        _screenHeight,
        SDL_WINDOW_OPENGL
    );
    if(_window == nullptr) {
        fatalError("SDL Window could not be created!");
    }

    // Создаем контекст OpenGl
    SDL_GLContext GLContext = SDL_GL_CreateContext(_window);
    if (GLContext == nullptr) {
        fatalError("SDL_GL context could not be created!");
    }

    // Создаем glew -- я хз что это
    //
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        fatalError("Could not initialize glew!");
    }

    // Включаем двойной буффер
    // Он делаем смену кадра плавнее, за счет ресурсов пк
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Устанавливаем цвет для рисования
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

// Глвный цикл игры
void Game::gameLoop() {
    while (_gameState != GameState::EXIT) {

        // Обрабатываем события
        processInput();

        // Рисуем
        drawGame();
    }
}

// Евенты игры
void Game::processInput() {
    SDL_Event evnt;
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type)
        {
            // Выход из игры
        case SDL_QUIT:
            _gameState = GameState::EXIT;
            break;
            // Позиция мыши
        case SDL_MOUSEMOTION:
            std::cout
                << evnt.motion.x
                << " "
                << evnt.motion.y
            << std::endl;
            break;
        }
    }
}

void Game::drawGame() {
    // хз
    glClearDepth(1.0);
    // хз
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // хз
    glEnableClientState(GL_COLOR_ARRAY);

    // Задаем что собираемся рисовать треугольник
    glBegin(GL_TRIANGLES);
        // Цвет
        glColor3f(0.0f, 1.0f, 0.0f);
        // Вершины
        glVertex2f(0, 0);
        glVertex2f(0, 500);
        glVertex2f(500, 500);
    glEnd();

    // Сменить буффер >> смотри SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SwapWindow(_window);
}