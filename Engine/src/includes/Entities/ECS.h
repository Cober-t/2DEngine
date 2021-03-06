#pragma once
#include <Core.h>
#include <Components.h>

const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

namespace Cober {
	
	////////////////////////////////////////////////////////////////
	// +++++ ENTITY +++++++++++++++++++++++++++++++++++++++++++++ //
	class Entity {
	public:
		Entity(int id) : id(id), registry(nullptr) {};
		Entity(const Entity& entity) = default;

		int GetID() const { return id; }

		Entity& operator =(const Entity& other) = default;
		bool operator ==(const Entity& other) const { return id == other.id; };
		bool operator !=(const Entity& other) const { return id != other.id; };
		bool operator < (const Entity& other) const { return id <  other.id; };
		bool operator > (const Entity& other) const { return id >  other.id; };

		template<typename TComponent, 
				 typename ...TArgs>		void AddComponent(TArgs&& ...args);
		template<typename TComponent>	void RemoveComponent();
		template<typename TComponent>	bool HasComponent() const;
		template<typename TComponent>	TComponent& GetComponent() const;

		class Registry* registry;	// Alternative to Forward Declaration

	private:
		int id;
	};

	////////////////////////////////////////////////////////////////
	// +++++ SYSTEM +++++++++++++++++++++++++++++++++++++++++++++ //
	class System {
	public:
		System() = default;
		~System() = default;

		void AddEntityToSystem(Entity entity);
		void RemoveEntityFromSystem(Entity entity);

		std::vector<Entity> GetSystemEntities() const { return entities; }
		const Signature& GetComponentSignature() const { return componentSignature; }

		// Defines the component type that entities must have to be considered by the system
		template<typename TComponent>	void RequireComponent();
	private:
		Signature componentSignature;
		std::vector<Entity> entities;
	};


	////////////////////////////////////////////////////////////////
	// +++++ POOL +++++++++++++++++++++++++++++++++++++++++++++++ //
	class IPool {
	public:
		virtual ~IPool() {}
	};

	template<typename T>
	class Pool : public IPool {
	public:
		Pool(int size = 100) { data.resize(size); }
		virtual ~Pool() = default;

		bool IsEmpty() const { return data.empty(); }
		int	GetSize() const { return data.size(); }
		void Resize(int n) { data.resize(n); }

		void Clear() { data.clear(); }
		void Add(T object) { data, push_back(object); }
		void Set(int index, T object) { data[index] = object; }

		T& Get(int index) { return static_cast<T&>(data[index]); }
		T& operator [](unsigned int index) { return data[index]; }
	private:
		std::vector<T> data;
	};

	////////////////////////////////////////////////////////////////
	// +++++ REGISTRY +++++++++++++++++++++++++++++++++++++++++++ //
	class Registry {
	public:
		Registry()  { Logger::Log("Registry constructor called"); };
		~Registry() { Logger::Log("Registry destructor called"); };

		void Update();
		
		Entity CreateEntity();
		//{
			//Entity entity = { m_Registry.create(), this };
			//entity.AddComponent<TransformComponent>();
			//auto& tag = entity.AddComponent<TagComponent>();
			//tag.Tag = name.empty() ? "Entity" : name;
			//enttOnScene.push_back(entity);
			//return entity;
		//}

		// Component management
		template<typename TComponent, 
				 typename ...TArgs>		void AddComponent(Entity entity, TArgs&& ...args);
		template<typename TComponent>	void RemoveComponent(Entity entity);
		template<typename TComponent>	bool HasComponent(Entity entity) const;
		template<typename TComponent>	TComponent& GetComponent(Entity entity) const;

		// System management
		template<typename TSystem, 
				 typename ...TArgs> 	void AddSystem(TArgs&& ...args);
		template<typename TSystem>		void RemoveSystem();
		template<typename TSystem>		bool HasSystem() const;
		template<typename TSystem>		TSystem& GetSystem() const;

		// Add the entity to the systems that are interested in it
		void AddEntityToSystems(Entity entity);
	private:
		int numEntities = 0;
		std::vector<Ref<IPool>> componentPools;

		std::vector<Signature> entityComponentSignatures;

		std::unordered_map<std::type_index, Ref<System>> systems;

		std::set<Entity> entitiesToBeAdded;
		std::set<Entity> entitiesToBeKilled;
	};

	////////////////////////////////////////////////////////////////
	// +++++ TEMPLATES ++++++++++++++++++++++++++++++++++++++++++ //
	template <typename TComponent>
	void System::RequireComponent() {
		const auto componentID = Component<TComponent>::GetID();
		componentSignature.set(componentID);
	}

	template<typename TSystem, typename ... TArgs>
	void Registry::AddSystem(TArgs&& ...args) {
		Ref<TSystem> newSystem(CreateRef<TSystem>(std::forward<TAgs>(args)...));
		systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
	}

	template<typename TSystem>
	void Registry::RemoveSystem() {
		auto system = systems.find(std::type_index(typeid(TSystem)));
		systems.erase(system);
	}

	template<typename TSystem>
	bool Registry::HasSystem() const {
		return systems.find( std::type_index(typeid(TSystem))) != systems.end();
	}

	template<typename TSystem>
	TSystem& Registry::GetSystem() const {
		auto system = systems.find(std::type_index(typeid(TSystem)));
		return *(std::static_pointer_cast<TSystem>(system->second));
	}

	template<typename TComponent, typename ...TArgs>
	void Registry::AddComponent(Entity entity, TArgs&& ...args) {
		const auto componentID = Component<TComponent>::GetID();
		const auto entityID = entity.GetID();

		if(componentID >= componentPools.size())
			componentPools.resize(componentID + 1, nullptr);
		
		if (!componentPools[componentID]) {
			Ref<Pool<TComponent>> newComponentPool = CreateRef<Pool<TComponent>>();
			componentPools[componentID] = newComponentPool;
		}

		Ref<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentID]);

		if (entityID >= componentPool->GetSize())
			componentPool->Resize(numEntities);

		TComponent newComponent(std::forward<TArgs>(args)...);
		componentPool->Set(entityID, newComponent);
		entityComponentSignatures[entityID].set(componentID);

		Logger::Log("Component ID = " + std::to_string(componentID) +	" was added to entity ID: " + std::to_string(entityID));
	}

	template<typename TComponent>
	void Registry::RemoveComponent(Entity entity) {
		const auto componentID = Component<TComponent>::GetID();
		const auto entityID = entity.GetID();

		entityComponentSignatures[entityID].set(componentID, false);
		Logger::Log("Component ID = " + std::to_string(componentID) + " was removed from entity ID: " + std::to_string(entityID));
	}

	template<typename TComponent>
	bool Registry::HasComponent(Entity entity) const {
		const auto componentID = Component<TComponent>::GetID();
		const auto entityID = entity.GetID();

		return entityComponentSignatures[entityID].test(componentID);
	}

	template<typename TComponent>
	TComponent& Registry::GetComponent(Entity entity) const {
		const auto componentID = Component<TComponent>::GetID();
		const auto entityID = entity.GetID();
		auto componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentID]);
		
		return componentPool->Get(entityID);
	}

	template<typename TComponent, typename ...TArgs>
	void Entity::AddComponent(TArgs&& ...args) {
		registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
	}

	template<typename TComponent>
	void Entity::RemoveComponent() {
		registry->RemoveComponent<TComponent>(*this);
	}

	template<typename TComponent>
	bool Entity::HasComponent() const {
		return registry->HasComponent<TComponent>(*this);
	}

	template<typename TComponent>
	TComponent& Entity::GetComponent() const {
		return registry->GetComponent<TComponent>(*this);
	}
}