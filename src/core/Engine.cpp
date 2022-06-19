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

        // Init ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        
        // [++++++++++ Setup Dear ImGui style ++++++++++]
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

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

            ImGui_ImplSDL2_ProcessEvent(&event);

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

        // [++++++++++ IMGUI ++++++++++]
        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();


        ImGui::Begin("Another Window");
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            isRunning = false;
        ImGui::End();
    }

    void Engine::Destroy() {
     
        ImGui_ImplSDLRenderer_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        m_window->CloseWindow();
    }
}