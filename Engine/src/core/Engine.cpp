#include <Engine.h>

namespace Cober {

    Engine* Engine::_instance = nullptr;

    Engine::Engine() : isRunning(false), enableGUI(true) {
        _instance = this;
        _registry = CreateUnique<Registry>();
        _timestep = CreateUnique<Timestep>();
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
        //_timestep->SetFPSLimit(60);
    }

    void Engine::Run() {

        Start();

        while(isRunning) {

            ProcessInputs();
            Update();

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

        // Add the systems that need to be processed in our game
        _registry->AddSystem<MovementSystem>();
        _registry->AddSystem<RenderSystem>();

        // Create som entities
        Entity tank = _registry->CreateEntity();

        // Add some components to the entity
        tank.AddComponent<Transform>(Vec2(10.0f, 30.0f), 0.0f, Vec2(1.0f, 1.0f));
        tank.AddComponent<Rigidbody>(Vec2(45.0f, 10.0f));
        tank.AddComponent<Sprite>(50, 50);
    }

    void Engine::Update() {

        _timestep->Update();  // Allow limit FPS

        _window->ClearWindow();

        // Update the registry to process the entities that are waiting to be created/deleted
        _registry->Update();

        // Ask all the "previous" frame time
        _registry->GetSystem<MovementSystem>().Update(_timestep->deltaTime);
        _registry->GetSystem<RenderSystem>().Update(_window->GetRenderer());
        //registry->GetSystem<CollisiontSystem>().Update();
        //registry->GetSystem<TerrainSystem>().Update();
        //registry->GetSystem<AISystem>().Update();


        _window->Render();
    }

    void Engine::Destroy() {
        _window->CloseWindow();
    }
}