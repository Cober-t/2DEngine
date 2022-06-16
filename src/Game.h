#ifndef GAME_H
#define GAME_H
#include<SDL2/SDL.h>
#include<string>

class Game {

	private:
        struct WindowData{
            std::string title;
            unsigned int width, height;
            bool VSync;
        };
        WindowData data;
        bool isRunning;
        SDL_Window* window;
	SDL_Renderer* renderer;
	public:
		Game();
		~Game();
		void Initialize();
		void Run();
		void Setup();
		void ProcessInputs();
		void Update();
		void Render();
		void Destroy();
};

#endif
