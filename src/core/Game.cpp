#include <Game.h>

namespace Cober {

    Game::Game() {
        isRunning = false;
        LOG("2DEngine Constructor!");
    }

    Game::~Game() {
        LOG("2DEngine Destructor!");
    }

    void Game::Initialize() {

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            LOG_ERROR("Error initializating SDL");
            return;
        }

        m_window = Window::Create(); 
       
        isRunning = true;
    }

    void Game::Run() {
        while(isRunning) {
            ProcessInputs();
            Update();
            m_window->Render();
        }
    }

    void Game::ProcessInputs() {

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                        isRunning = false;
                    break;
            }
        }
    }

    void Game::Update() {

    }

    void Game::Destroy() {
        m_window->CloseWindow();
        return;
    }
}