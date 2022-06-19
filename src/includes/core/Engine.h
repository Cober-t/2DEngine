#pragma once
#include <Window.h>
#include <Timestep.h>

namespace Cober {

	class Engine {
		private:
			bool isRunning;
			Unique<Window> m_window;
			Timestep timestep;
		public:
			Engine();
			~Engine();
			void Initialize();
			void ProcessInputs();
			void Run();
			void Start();
			void Update(Timestep timestep);
			void Destroy();
			Window& GetWindow() { return *m_window; }
	};
}