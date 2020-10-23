#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <bitset>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <type_traits>

//Type Aliases and Globals

using EntityID = std::uint32_t;

//Max number of entities in a scene;
const EntityID MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t;

//Max number of components on one entity;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

//Entity Manager======================================

class EntityManager
{
public:
	EntityManager()
	{
		for (EntityID id = 0; id < MAX_ENTITIES; id++)
			m_AvailableEntities.push(id);
	}

	EntityID CreateEntity()
	{
		EntityID id = m_AvailableEntities.front();
		m_AvailableEntities.pop();
		++m_LivingEntityCount;

		m_Entities.push_back(id);

		return id;
	}

	void DestroyEntity(EntityID entity)
	{
		m_Signatures[entity].reset();
		m_AvailableEntities.push(entity);

		--m_LivingEntityCount;

		std::vector<EntityID>::iterator position = std::find(m_Entities.begin(), m_Entities.end(), entity);
		if (position != m_Entities.end())
			m_Entities.erase(position);
	}

	void SetSignature(EntityID entity, Signature signature)
	{
		m_Signatures[entity] = signature;
	}

	Signature GetSignature(EntityID entity)
	{
		return m_Signatures[entity];
	}

private:
	friend class Registry;

	std::queue<EntityID> m_AvailableEntities{};

	std::vector<EntityID> m_Entities{};

	std::array<Signature, MAX_ENTITIES> m_Signatures{};

	uint32_t m_LivingEntityCount = 0;
};

//Component Array Interface==========================================

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(EntityID entity) = 0;
};

//Component Array

template<typename T>
class ComponentArray : public IComponentArray
{
public:
	void insert(EntityID entity, T component)
	{
		size_t newIndex = m_Size;
		m_EntityToIndexMap[entity] = newIndex;
		m_IndexToEntityMap[newIndex] = entity;
		m_ComponentArray[newIndex] = component;

		m_Entities.push_back(entity);

		++m_Size;
	}

	void remove(EntityID entity)
	{
		size_t indexOfRemovedEntity = m_EntityToIndexMap[entity];
		size_t indexOfLastElement = m_Size - 1;
		m_ComponentArray[indexOfRemovedEntity] = m_ComponentArray[indexOfLastElement];

		EntityID entityOfLastElement = m_IndexToEntityMap[indexOfLastElement];
		m_EntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		m_IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		m_EntityToIndexMap.erase(entity);
		m_IndexToEntityMap.erase(indexOfLastElement);

		for (size_t i = 0; i < m_Entities.size(); i++)
		{
			if(m_Entities[i] == entity)
			{
				m_Entities.erase(m_Entities.begin() + i);
				break;
			}
		}

		--m_Size;
	}

	T& get(EntityID entity)
	{
		return m_ComponentArray[m_EntityToIndexMap[entity]];
	}

	void EntityDestroyed(EntityID entity) override
	{
		if (m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end())
			remove(entity);
	}

	bool contains(EntityID entity)
	{
		return m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end();
	}

	size_t size() const
	{
		return m_Size;
	}

	std::vector<EntityID>& entities()
	{
		return m_Entities;
	}

	template<typename Func>
	void each(Func func)
	{
		for (size_t i = 0; i < m_Size; i++)
		{
			func(m_IndexToEntityMap[i], m_ComponentArray[i]);
		}
	}

	void reset()
	{
		while (m_Size != 0)
			remove(m_Entities[0]);
	}

	std::vector<EntityID>::iterator begin()
	{
		return m_Entities.begin();
	}

	std::vector<EntityID>::iterator end()
	{
		return m_Entities.end();
	}

	std::vector<EntityID>::const_iterator begin() const
	{
		return m_Entities.begin();
	}

	std::vector<EntityID>::const_iterator end() const
	{
		return m_Entities.end();
	}

private:
	std::array<T, MAX_ENTITIES> m_ComponentArray;

	std::vector<EntityID> m_Entities;

	std::unordered_map<EntityID, size_t> m_EntityToIndexMap;
	std::unordered_map<size_t, EntityID> m_IndexToEntityMap;

	size_t m_Size;
};

//Component Manager============================================

class Registry;

class ComponentManager
{
	friend Registry;
public:

	template<typename T>
	void RegisterComponent()
	{
		const char* name = typeid(T).name();

		if (m_ComponentTypes.find(name) == m_ComponentTypes.end())
		{
			m_ComponentTypes.insert({ name, m_NextComponentType });
			m_ComponentArrays.insert({ name, std::make_shared<ComponentArray<T>>() });

			++m_NextComponentType;
		}
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* name = typeid(T).name();

		if (m_ComponentTypes.find(name) == m_ComponentTypes.end())
			RegisterComponent<T>();

		return m_ComponentTypes[name];
	}

	template<typename T>
	void AddComponent(EntityID entity, T Component)
	{
		const char* name = typeid(T).name();
		if (m_ComponentTypes.find(name) == m_ComponentTypes.end())
			RegisterComponent<T>();

		GetComponentArray<T>()->insert(entity, Component);
	}

	template<typename T>
	void RemoveComponent(EntityID entity)
	{
		GetComponentArray<T>()->remove(entity);
	}

	template<typename T>
	T& GetComponent(EntityID entity)
	{
		return GetComponentArray<T>()->get(entity);
	}

	void EntityDestroyed(EntityID entity)
	{
		for (auto const& pair : m_ComponentArrays)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}

private:
	std::unordered_map<const char*, ComponentType> m_ComponentTypes{};
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_ComponentArrays{};


	ComponentType m_NextComponentType = 0;


	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const char* name = typeid(T).name();

		if (m_ComponentTypes.find(name) != m_ComponentTypes.end())
			return std::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[name]);

		return nullptr;

	}
};

//Registry

class Registry
{
public:
	Registry()
	{
		m_EntityManager = std::make_unique<EntityManager>();
		m_ComponentManager = std::make_unique<ComponentManager>();
	}

	EntityID create()
	{
		EntityID ent = m_EntityManager->CreateEntity();
		return ent;
	}

	void destroy(EntityID entity)
	{
		m_EntityManager->DestroyEntity(entity);
		m_ComponentManager->EntityDestroyed(entity);
	}

	template<typename T>
	void add(EntityID entity, T component)
	{
		m_ComponentManager->AddComponent(entity, component);

		auto signature = m_EntityManager->GetSignature(entity);
		signature.set(m_ComponentManager->GetComponentType<T>(), true);
		m_EntityManager->SetSignature(entity, signature);
	}

	template<typename T>
	void remove(EntityID entity)
	{
		m_ComponentManager->RemoveComponent<T>(entity);

		auto signature = m_EntityManager->GetSignature(entity);
		signature.set(m_ComponentManager->GetComponentType<T>(), false);
		m_EntityManager->SetSignature(entity, signature);
	}

	template<typename T>
	T& get(EntityID entity)
	{
		return m_ComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	bool has(EntityID entity)
	{
		auto signature = m_EntityManager->GetSignature(entity);
		return signature[m_ComponentManager->GetComponentType<T>()];
	}

	template<typename T>
	ComponentArray<T>* view()
	{
		return m_ComponentManager->GetComponentArray<T>().get();
	}

	//Current Problem Child----------------Find a better way to do this
	template<typename T, typename U>
	ComponentArray<std::pair<T, U>>* view()
	{
		ComponentArray<T>& t = *m_ComponentManager->GetComponentArray<T>().get();
		ComponentArray<U>& u = *m_ComponentManager->GetComponentArray<U>().get();

		if (m_ComponentManager->GetComponentArray<std::pair<T, U>>() == nullptr)
			m_ComponentManager->RegisterComponent<std::pair<T, U>>();
		else
			m_ComponentManager->GetComponentArray<std::pair<T, U>>()->reset();

		for (size_t i = 0; i < u.entities().size(); i++)
		{
			if (t.contains(u.entities()[i]))
			{
				m_ComponentManager->GetComponentArray<std::pair<T, U>>()->insert(u.entities()[i],
					std::make_pair(t.get(u.entities()[i]), u.get(u.entities()[i])));
			}
		}

		return m_ComponentManager->GetComponentArray<std::pair<T, U>>().get();
	}

	template<typename Function>
	void each(Function func)
	{
		for (size_t i = 0; i < m_EntityManager->m_Entities.size(); i++)
		{
			func(m_EntityManager->m_Entities[i]);
		}
	}

private:
	std::unique_ptr<EntityManager> m_EntityManager;
	std::unique_ptr<ComponentManager> m_ComponentManager;
};