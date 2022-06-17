#pragma once
#include <Window.h>

namespace Cober {

	class Game {
		private:
			bool isRunning;
			Unique<Window> m_window;
		public:
			Game();
			~Game();
			void Initialize();
			void ProcessInputs();
			void Run();
			void Update();
			void Render();
			void Destroy();
			Window& GetWindow() { return *m_window; }
	};
}