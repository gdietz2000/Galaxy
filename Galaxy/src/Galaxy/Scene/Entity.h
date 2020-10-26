#pragma once

#include "Scene.h"

namespace Galaxy
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(EntityID handle, Scene* scene)
			: m_Handle(handle), m_Scene(scene) {}

		template<typename T>
		T& AddComponent(T Component = T())
		{
			return m_Scene->m_Registry->add<T>(m_Handle, Component);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry->has<T>(m_Handle);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->m_Registry->get<T>(m_Handle);
		}

		template<typename T>
		void RemoveComponent()
		{
			m_Scene->m_Registry->remove<T>(m_Handle);
		}

		operator bool() const { return m_Handle != (uint32_t)-1; }
		operator uint32_t() const { return (uint32_t)m_Handle; }

		bool operator==(const Entity& other) const { return m_Handle == other.m_Handle && m_Scene == other.m_Scene; }
		bool operator!=(const Entity& other) const { return !(*this == other); }

	private:
		EntityID m_Handle = -1;
		Scene* m_Scene = nullptr;
	};
}
