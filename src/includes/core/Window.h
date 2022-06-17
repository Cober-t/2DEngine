#pragma once
#include <Core.h>

namespace Cober {

    class Window {

    private:
        struct WindowData{
            const char* title;
            unsigned int width, height;
            bool VSync;

            WindowData() : title(NULL), width(1920), height(1080), VSync(true) {}
        };
        WindowData data;
        SDL_Window* window;
        SDL_Renderer* renderer;
    public:
        Window(const WindowData& data);
        ~Window();

        static Unique<Window> Create(const WindowData& data = WindowData());
        bool CreateWindow();
        bool CreateRenderer();
        SDL_Window*   GetNativeWindow() { return window; }
        SDL_Renderer* GetRenderer() { return renderer; }
        void Render();
        void CloseWindow();
    };
}