#include <Engine.h>

namespace Cober {

    Engine* Engine::_instance = nullptr;

    Engine::Engine() : isRunning(false), enableGUI(true) {
        _instance = this;
        registry = CreateUnique<Registry>();
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

        _window = Window::Create(); 
        GUISystem::Init();
       
        isRunning = true;
        timestep.SetFPSLimit(60);
    }

    void Engine::Run() {

        Start();

        while(isRunning) {

            ProcessInputs();
            Update(timestep);

            if (enableGUI) {
                GUISystem::Begin();
                GUISystem::Update();
                GUISystem::End();
            }
            _window->RenderDisplay();
        }
    }
   
    void Engine::ProcessInputs() {

        SDL_Event event;
        while(SDL_PollEvent(&event)) {

            ImGui_ImplSDL2_ProcessEvent(&event);

            switch(event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                        isRunning = false;
                    if (event.key.keysym.sym == SDLK_d)
                        enableGUI = enableGUI == true ? false : true;
                    break;
            }
        }
    }

    void Engine::Start() {
        // Create som entities
        Entity tank = registry->CreateEntity();

        // Add some components to the entity
        //registry->AddComponent<Transform>(tank, Vec2(1.0f), 0.0f, Vec2(1.0f));
        //registry->AddComponent<Rigidbody>(tank, Vec2(50.0f, 0.0f));
        tank.AddComponent<Transform>(Vec2(1.0f), 0.0f, Vec2(1.0f));
        tank.AddComponent<Rigidbody>(Vec2(50.0f, 0.0f));
        tank.RemoveComponent<Rigidbody>();
    }

    void Engine::Update(Timestep timestep) {

        timestep.Update();  // Allow limit FPS

        _window->ClearWindow();

        // TODO: Render entities
        // ...
        // ...

        _window->Render();
    }

    void Engine::Destroy() {
        _window->CloseWindow();
    }
}