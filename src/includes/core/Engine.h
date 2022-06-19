#pragma once
#include <Window.h>
#include <Timestep.h>

namespace Cober {

	class Engine {
		private:
			bool isRunning;
			Unique<Window> m_window;
			Timestep timestep;
			float lastFrameTime = 0.0f;
			float timeInSeconds = 0.0f;
			int frames = 0;
		public:
			Engine();
			~Engine();
			void Initialize();
			void ProcessInputs();
			void Run();
			void Start();
			void Update(Timestep time);
			void Render();
			void Destroy();
			Window& GetWindow() { return *m_window; }
	};
}