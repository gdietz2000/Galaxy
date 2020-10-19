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
		void AddComponent(T Component = T())
		{
			m_Scene->m_Registry->add<T>(m_Handle, Component);
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

	private:
		EntityID m_Handle = -1;
		Scene* m_Scene = nullptr;
	};
}
