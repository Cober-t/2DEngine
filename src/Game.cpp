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
    
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL" << std::endl;
        return;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    data.width  = displayMode.w;
    data.height = displayMode.h;

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        data.width, data.height,
        SDL_WINDOW_BORDERLESS
    );
    
    if (!window) {
       std::cerr << "Error creating SDL window" << std::endl;
       return;     
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer){
	std::cerr << "Error creating SDL renderer" << std::endl;
	return;
    }
    
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    isRunning = true;
}

void Game::Run() {
    Setup();	
    while(isRunning) {
	ProcessInputs();
	Update();
      	Render();
    }
}

void Game::Destroy() {

    SDL_DestroyRenderer(renderer);
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

void Game::Setup() {

}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
