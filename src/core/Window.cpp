#include <Window.h>

namespace Cober {

    static bool CheckError(int error, const char* errormsg) {
        if (error == 0) {
            std::cerr << errormsg << ":\n" << SDL_GetError() << std::endl;
            return true;
        }
        return false;
    }

    Unique<Window> Window::Create(const WindowData& data) {

        return CreateUnique<Window>(data);
    }

    Window::Window(const WindowData& data) { 
        // Check value 0 on failure or 1 on success
        if (CheckError(CreateWindow(), "Window is null") ||
            CheckError(CreateRenderer(), "Error creating SDL renderer"))
            return;
    }

    Window::~Window() { 
        
    }

    bool Window::CreateWindow() {
        
        int flags = SDL_WINDOW_BORDERLESS;
        window = SDL_CreateWindow(
            data.title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            data.width, data.height,
            flags
        );
        return window;
    }

    bool Window::CreateRenderer() {

        int flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        renderer = SDL_CreateRenderer(window, -1,flags);

        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

        return renderer;
    }

    void Window::Render() {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    void Window::CloseWindow() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}