#pragma once
#include <Window.h>

namespace Cober {

	class Engine {
		private:
			bool isRunning;
			Unique<Window> m_window;
		public:
			Engine();
			~Engine();
			void Initialize();
			void ProcessInputs();
			void Run();
			void Update();
			void Render();
			void Destroy();
			Window& GetWindow() { return *m_window; }
	};
}