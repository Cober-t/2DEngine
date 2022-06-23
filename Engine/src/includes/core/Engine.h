#pragma once
#include <Window.h>
#include <Timestep.h>
#include <GUISystem.h>
#include <ECS.h>
#include <AssetManager.h>
#include <Components.h>
#include <Systems/MovementSystem.h>
#include <Systems/RenderSystem.h>

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
		void Update();
		void Destroy();

		void CloseEngine() { isRunning = false; }
		Window& GetWindow() { return *_window; }
	private:
		bool isRunning;
		bool enableGUI;
		Unique<Window> _window;
		Unique<Timestep> _timestep;
		Unique<Registry> _registry;
		Unique<AssetManager> _assetManager;
	private:
		static Engine* _instance;
		friend int ::main(int argc, char** argv);
	};
}