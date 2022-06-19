#pragma once
#include <Core.h>

namespace Cober {

	class Timestep {
	public:
		Timestep(float time = 0.0f)
			: FPS_Limit(60), lastFrameTime(0), frames(0), limit(false) { }

		void Update() {
			// Limit FrameRate
			if (limit) {
				int timeToWait = 1000 / FPS_Limit - (SDL_GetTicks() - lastFrameTime);
				if (timeToWait > 0 && timeToWait <= 1000 / FPS_Limit)
					SDL_Delay(timeToWait);
			}

			deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0;
			lastFrameTime = SDL_GetTicks();
		}
		void SetFPSLimit(float frames) {
			if (frames > 60)
				frames = 60;
			FPS_Limit = frames;
		}
		void UnlockFPSLimit() { limit = false; }
		double DeltaTime() { return deltaTime; }
	public:
		uint32_t lastFrameTime;
		uint32_t FPS_Limit;
		uint32_t frames;
		bool	 limit;
		double	 deltaTime;
	};
}