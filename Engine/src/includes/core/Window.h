#pragma once
#include <Core.h>

namespace Cober {

    class Window {

    private:
        struct WindowData{
            const char* title;
            unsigned int width, height;
            bool VSync;

            WindowData() : title(NULL), width(800), height(600), VSync(true) {}
        };
        WindowData data;
        SDL_Window* window;
        SDL_Surface* surface;
        SDL_Renderer* renderer;
        SDL_Texture* screenTexture;
    public:
        Window(const WindowData& data);
        ~Window();

        static Unique<Window> Create(const WindowData& data = WindowData());
        bool CreateWindow();
        bool CreateRenderer();
        SDL_Window*   GetNativeWindow() { return window; }
        SDL_Renderer* GetRenderer() { return renderer; }
        uint32_t ScreenTexture() { return (uint32_t)&screenTexture; }
        void ClearWindow(Uint8 r = 21, Uint8 g = 21, Uint8 b = 36, Uint8 k = 255);
        void Render();
        void RenderDisplay();
        void CloseWindow();
    };
}