#include <Engine.h>

namespace Cober {

    Engine* Engine::_instance = nullptr;

    Engine::Engine() : isRunning(false), enableGUI(true) {
        _instance = this;
        Logger::Log("2DEngine Constructor!");
        _timestep = CreateUnique<Timestep>();
        _registry = CreateUnique<Registry>();
        _assetManager = CreateUnique<AssetManager>();
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
            _window->Render();
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

        // Add assets
        SDL_Renderer* renderer = _window->GetRenderer();
        _assetManager->AddTexture("cat", "../assets/images/tank-panther-right.png");

        // Create som entities
        Entity tank = _registry->CreateEntity();

        // Add some components to the entity
        tank.AddComponent<Transform>(Vec2(10.0, 10.0), 0, Vec2(1.0, 1.0));
        tank.AddComponent<Rigidbody>(Vec2(45.0f, 0.0f));
        tank.AddComponent<Sprite>("cat", 128*3, 128*3);
    }

    void Engine::Update() {

        _timestep->Update();  // Allow limit FPS

        // Update the registry to process the entities that are waiting to be created/deleted
        _registry->Update();

        // Ask all the "previous" frame time
        _registry->GetSystem<MovementSystem>().Update(_timestep->deltaTime);

        _window->ClearWindow();
        _registry->GetSystem<RenderSystem>().Update(_window->GetRenderer(), _assetManager);
    }

    void Engine::Destroy() {
        _window->CloseWindow();
    }
}