#pragma once
#include <Window.h>
#include <Timestep.h>
#include <GUISystem.h>
#include <ECS.h>
#include <Component.h>

namespace Cober {

	class Engine {
	public:
		Engine();
		~Engine();
		static Engine& Get() { return *_instance; }
		
		void Initialize();

		void Start();
		void Run();

		void ProcessInputs();
		void Update(Timestep timestep);
		void Destroy();

		void CloseEngine() { isRunning = false; }
		Window& GetWindow() { return *_window; }
	private:
		bool isRunning;
		bool enableGUI;
		Unique<Window> _window;
		Timestep timestep;
		Unique<Registry> registry;
	private:
		static Engine* _instance;
		friend int ::main(int argc, char** argv);
	};
}