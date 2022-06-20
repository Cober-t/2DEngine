#include <Window.h>

namespace Cober {

    static bool CheckError(bool error, const char* errormsg = nullptr) {
        if (!error) {
            if (errormsg)
                std::cerr << errormsg << ":" << "\n";
            Logger::Error(SDL_GetError());
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
        
        int flags = SDL_WINDOW_RESIZABLE |
                    SDL_WINDOW_ALLOW_HIGHDPI | 
                    SDL_WINDOW_BORDERLESS;
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

        int flags = SDL_RENDERER_ACCELERATED | 
                    SDL_RENDERER_PRESENTVSYNC;
        renderer = SDL_CreateRenderer(window, -1, flags);

        //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

        return renderer;
    }

    void Window::Render() {

        // TEST
        {
            //Loads a PNG texture
            surface = IMG_Load("../assets/images/blendTest.png");
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            
            // Rectangle destination for the texture
            if (surface) {
                SDL_Rect rect = { 10, 10, surface->w / 2, surface->h / 2 };
                SDL_RenderCopy(renderer, texture, NULL, &rect);
            }

            SDL_DestroyTexture(texture);
        }
    }
    
    void Window::ClearWindow(Uint8 r, Uint8 g, Uint8 b, Uint8 k) {
        SDL_SetRenderDrawColor(renderer, r, g, b, k);
        SDL_RenderClear(renderer);
    }

    void Window::RenderDisplay() {
        SDL_FreeSurface(surface);
        SDL_RenderPresent(renderer);
    }

    void Window::CloseWindow() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}