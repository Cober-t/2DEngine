#pragma once

#include <Core.h>
#define vec2 glm::vec2

namespace Cober {

	struct IComponent {
	protected:
		static int nextID;
	};

	// Used to assign a unique IDs to a component type
	template <typename T>
	class Component : public IComponent {
		static int GetID() {
			static auto id = nextID++;
			return id;
		}
	};

	struct Transform {
		vec2 position = {0.0f, 0.0f};
		float rotation = 0.0f;
		vec2 scale = { 0.0f, 0.0f };

		Transform() = default;
		Transform(const Transform&) = default;
		Transform(vec2 pos, float rot, vec2 sc)
			: position(pos), rotation(rot), scale(sc) {};
	};

	struct Tag{
		std::string tag;

		Tag() = default;
		Tag(const Tag&) = default;;
		Tag(const std::string& tag) : tag(tag) {};
	};
}
