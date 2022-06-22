#pragma once

#include <Core.h>
#include <ECS.h>
#include <Components.h>

namespace Cober {

	class RenderSystem : public System {
	public:
		RenderSystem() {
			RequireComponent<Transform>();
			RequireComponent<Sprite>();
		}

		void Update(SDL_Renderer* renderer) {
			
			for (auto entity : GetSystemEntities()) {
				auto& transform = entity.GetComponent<Transform>();
				const auto& sprite = entity.GetComponent<Sprite>();

				SDL_Rect objRect = {
					static_cast<int>(transform.position.x),
					static_cast<int>(transform.position.y),
					sprite.w,
					sprite.h
				};

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(renderer, &objRect);
			}
		}
	};
}
