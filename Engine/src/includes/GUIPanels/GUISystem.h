#pragma once

#include <Core.h>

namespace Cober {

	class GUISystem {
		public:
			GUISystem();
			~GUISystem();

			static void Create();
			// TODO: SDL_Event API
			static void OnEvent(SDL_Event& event);
			static void Begin();
			static void End();

			void SetDarkThemeColors();
		private:
	};
}
