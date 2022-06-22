#pragma once
#include <Core.h>
#include <Component.h>

const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

namespace Cober {
	
	////////////////////////////////////////////////////////////////
	// +++++ ENTITY +++++++++++++++++++++++++++++++++++++++++++++ //
	class Entity {
	public:
		Entity(int id) : id(id) {};
		Entity(const Entity& entity) = default;

		int GetID() const { return id; }

		Entity& operator =(const Entity& other) = default;
		bool operator ==(const Entity& other) const { return id == other.id; };
		bool operator !=(const Entity& other) const { return id != other.id; };
		bool operator < (const Entity& other) const { return id <  other.id; };
		bool operator > (const Entity& other) const { return id >  other.id; };

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
		template<typename TComponent>
		void RequireComponent();
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
		Pool(int size = 100) { Resize(size); }
		virtual ~Pool() = default;

		bool IsEmpty() const { return data.empty(); }
		int	GetSize() const { return data.size(); }
		void Resize(int n) { data.reisze(n); }

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
		Registry() = default;

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
		template<typename TComponent, typename ...TArgs>
		void AddComponent(Entity entity, TArgs&& ...args);
		template<typename TComponent>
		void RemoveComponent(Entity entity);
		template<typename TComponent>
		bool HasComponent(Entity entity) const;

		// System management
		template<typename TSystem, typename ...TArgs>
		void AddSystem(TArgs&& ...args);
		template<typename TSystem>
		void RemoveSystem();
		template<typename TSystem>
		bool HasSystem() const;
		template<typename TSystem>
		TSystem& GetSystem() const;

		// Add the entity to the systems that are interested in it
		void AddEntityToSystems(Entity entity);
	private:
		template<typename T>
		T& FindSystem();
	private:
		int numEntities = 0;
		std::vector<IPool*> componentPools;

		std::vector<Signature> entityComponentSignatures;

		std::unordered_map<std::type_index, System*> systems;

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
		TSystem* newSystem(new TSystem(std::forward<TAgs>(args)...));
		systems.emplace{ std::type_index(typeid(TSystem)) , newSystem };
	}

	template<typename TSystem>
	void Registry::RemoveSystem() {
		systems.erase(FindSystem<TSystem>());
	}

	template<typename TSystem>
	bool Registry::HasSystem() const {
		return systems.find( std::type_index(typeid(TSystem))) != systems.end();
	}

	template<typename TSystem>
	TSystem& Registry::GetSystem() const {
		return FindSystem<TSystem>().second;
	}

	template<typename TComponent, typename ...TArgs>
	void Registry::AddComponent(Entity entity, TArgs&& ...args) {
		const auto componentID = Component<TComponent>::GetID();
		const auto entityID = entity.GetID();

		if(componentID >= componentPools.size())
			componentPools.resize(componentID + 1, nullptr);
		
		if (!componentPools[componentID]) {
			Pool<TComponent>* newComponentPool = Pool<TComponent>();
			componentPools[componentID] = newComponentPool;
		}

		Pool<TComponent>* componentPool = componentPools[componentID];

		if (entityID >= componentPool->GetSize())
			componentPool->Resize(numEntities);

		TComponent newComponent(std::forward<TArgs>(args)...);
		componentPool->Set(entityID, newComponent);
		entityComponentSignature[entityID].set(componentID);
	}

	template<typename TComponent>
	void Registry::RemoveComponent(Entity entity) {
		const auto componentID = Component<TComponent>::GetID();
		const auto entityID = entity.GetID();

		entityComponentSignatures[entityID].set(componentID, false);
	}

	template<typename TComponent>
	bool Registry::HasComponent(Entity entity) const {
		const auto componentID = Component<TComponent>::GetID();
		const auto entityID = entity.GetID();

		return entityComponentSignatures[entityID].test(componentID);
	}

	template<typename T>
	T& Registry::FindSystem() {
		return systems.find(std::type_index(typeid(T)));
	}
}