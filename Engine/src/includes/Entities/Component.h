#pragma once

#include <Core.h>
#define vec2 glm::vec2

namespace Cober {

	struct ID {
		UUID id;

		ID() = default;
		ID(const ID&) = default;
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
