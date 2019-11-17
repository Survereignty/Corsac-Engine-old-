#include "Game.h"

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
    _music = nullptr;
    renderer = nullptr;
}

Game::~Game()
{
    delete renderer;
    SDL_Quit();
}

void Game::run() {
    initSystems();

    gameLoop();
}

// Инициализация
void Game::initSystems() {

    // SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    // MIX
    Mix_Init(MIX_INIT_MP3);

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
    try {
        renderer = new Vulkan();
    } catch (std::exception const &ex) {
        std::cout << ex.what() << std::endl;
    }


    // Ставим песню
    // Настраиваем качество
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    // Загружаем
    _music = Mix_LoadMUS("./bin/data/sdn/Smash Mouth All Star.mp3");
}

// Главный цикл игры
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
            /*std::cout
                << evnt.motion.x
                << " "
                << evnt.motion.y
            << std::endl;*/
            break;
        }
    }
}

// Рисуем тут
void Game::drawGame() {

    // Циклим музяку
    if (!Mix_PlayingMusic()) {
        Mix_PlayMusic(_music, 1);
    } // Громкость 0-100
    Mix_VolumeMusic(10);

}