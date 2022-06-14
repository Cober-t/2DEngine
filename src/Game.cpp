#include<iostream>
#include<GL/glew.h>
#include<imgui/imgui.h>
#include<imgui/imgui_impl_sdl.h>
#include"Game.h"

#define GLEW_STATIC

Game::Game() {
    isRunning = false;
	std::cout << "2DEngine Constructor!" << std::endl;
}

Game::~Game(){
	std::cout << "2DEngine Destructor!" << std::endl;
}

void Game::Initialize() {

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL" << std::endl;
        return;
    }
    
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL
    );
    
    if (!window) {
       std::cerr << "Error creating SDL window" << std::endl;
       return;     
    }
    
    context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "Error creating Window context" << std::endl;
        return;
    }
    
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error initializing GLEW" << std::endl;
        return;
    }
    
    std::cout << "Opengl Info" << std::endl;
    std::cout << "Vendor:\t\t" << (const char*)glGetString(GL_RENDERER) << std::endl;
    std::cout << "Renderer:\t" << (const char*)glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL:\t\t" << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    
    
    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    //ImGui_ImplSDL2_InitForOpenGL(window, (void*)true);
    /*
    ImGui_ImplOpenGL3_Init("330");
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    */
    
    isRunning = true;
}

void Game::Run(){
	
	while(isRunning) {
		ProcessInputs();
		Update();
        Render();
	}
}

void Game::Destroy() {

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
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

void Game::Render() {
    
    SDL_GL_SetSwapInterval(1);
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
}
