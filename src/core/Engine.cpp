#include <Engine.h>

namespace Cober {

    Engine::Engine() {
        isRunning = false;
        LOG("2DEngine Constructor!");
    }

    Engine::~Engine() {
        LOG("2DEngine Destructor!");
    }

    void Engine::Initialize() {

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            LOG_ERROR("Error initializating SDL");
            return;
        }

        m_window = Window::Create(); 
       
        isRunning = true;
    }

    void Engine::Run() {
        while(isRunning) {
            ProcessInputs();
            Update();
            m_window->Render();
        }
    }

    void Engine::ProcessInputs() {

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

    void Engine::Update() {

    }

    void Engine::Destroy() {
        m_window->CloseWindow();
        return;
    }
}