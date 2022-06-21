#pragma once
#include <Core.h>
#include <Entity.h>

const unsigned int MAX_COMPONENTES = 32;
typedef std::bitset<MAX_COMPONENTES> Signature;

namespace Cober {

	class System {
	public:
		System() = default;
		~System() = default;

		void AddEntity(Entity ent);
		void RemoveEntity(Entity ent);

		std::vector<Entity> GetSystemEntities() const { return entities; }
		const Signature& GetComponentSignature() const { return componentSignature; }

		// Defines the component type that entities must have to be considered by the system
		template<typename TComponent> 
		void RequireComponent();
	private:
		Signature componentSignature;
		std::vector<Entity> entities;
	};

	template <typename TComponent>
	void System::RequireComponent() {
		const auto componentID = Component<TComponent>::GetID();
		componentSignature.set(componentID);
	}
}
