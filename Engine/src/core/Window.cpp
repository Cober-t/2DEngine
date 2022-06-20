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

        // Init ImGui renderer
        ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer_Init(renderer);
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

        SDL_SetRenderDrawColor(renderer, 255, 101, 0, 255);
        SDL_RenderClear(renderer);

        // Loads a PNG texture
        SDL_Surface* surface = IMG_Load("../assets/images/blendTest.png");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        // Rectangle destination for the texture
        if (surface) {
            SDL_Rect rect = { 10, 10, surface->w / 4, surface->h / 5 };
            SDL_RenderCopy(renderer, texture, NULL, &rect);
        }
        SDL_DestroyTexture(texture);

        //if (enableGUI)
        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        //}
        SDL_RenderPresent(renderer);
    }

    void Window::CloseWindow() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}