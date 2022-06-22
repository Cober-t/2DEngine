#pragma once

#include <Core.h>
#include <ECS.h>
#include <Components.h>

namespace Cober {
	
	class MovementSystem: public System {
	public:
		MovementSystem() {
			RequireComponent<Transform>();
			RequireComponent<Rigidbody>();
		}

		void Update(double deltaTime) {

			for (auto entity : GetSystemEntities()) {
				auto& transform = entity.GetComponent<Transform>();
				const auto& rigidbody = entity.GetComponent<Rigidbody>();

				transform.position.x += rigidbody.velocity.x * deltaTime;
				transform.position.y += rigidbody.velocity.y * deltaTime;

				//Logger::Log("Entity ID = " +
				//	std::to_string(entity.GetID()) +
				//	" position is now (" +
				//	std::to_string(transform.position.x) +
				//	", " +
				//	std::to_string(transform.position.y) + ")");
			}
		}
	};
}