#pragma once

#include <Core.h>
#include <Window.h>
#include <Engine.h>

namespace Cober {

	class GUISystem {
		public:
			GUISystem();
			~GUISystem();

			// TODO: SDL_Event API
			void OnEvent(SDL_Event& event);

			static void Init();
			static void Begin();
			static void Update();
			static void End();
	};
}
