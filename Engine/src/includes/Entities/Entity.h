#pragma once
#include <Core.h>
#include <Component.h>

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

	class Entity {
	public:
		Entity() = default;
		Entity(const Entity& entity) = default;

		//CreateEntity(UUID(), "New Entity");
		Entity CreateEntity(UUID id, const std::string& name) {
			
			//Entity entity = { m_Registry.create(), this };
			//entity.AddComponent<IDComponent>(uuid);
			//entity.AddComponent<TransformComponent>();
			//auto& tag = entity.AddComponent<TagComponent>();
			//tag.Tag = name.empty() ? "Entity" : name;
			//enttOnScene.push_back(entity);
			//return entity;
		}
		
		UUID GetID() { return GetComponent<ID>().id; }

		Entity& operator =(const Entity& other) = default;
		bool operator ==(const Entity& other) const { return GetID() == entity.GetID(); };
		bool operator !=(const Entity& other) const { return GetID() != entity.GetID(); };
		bool operator < (const Entity& other) const { return GetID() < entity.GetID();  };
		bool operator > (const Entity& other) const { return GetID() > entity.GetID();  };

		template<typename T>
		T& GetComponent();

		template<typename T>
		T& Addomponent();

		template<typename T>
		void RemoveComponent();
	};

	class Registry {
	public:
	private:

	};
}