#include <Engine.h>

namespace Cober {

    Engine::Engine() {
        isRunning = false;
        Logger::Log("2DEngine Constructor!");
    }

    Engine::~Engine() {
        Logger::Log("2DEngine Destructor!");
    }

    void Engine::Initialize() {

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            Logger::Error("Error initializating SDL");
            return;
        }
        m_window = Window::Create(); 
        isRunning = true;
        timestep.SetFPSLimit(60);
    }

    void Engine::Run() {
        
        Start();

        while(isRunning) {

            timestep.Update();

            ProcessInputs();
            Update(timestep);
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

    void Engine::Start() {

    }

    void Engine::Update(Timestep timestep) {

    }

    void Engine::Destroy() {
        m_window->CloseWindow();
    }
}