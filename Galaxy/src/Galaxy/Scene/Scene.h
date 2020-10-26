#pragma once

#include "Managers.h"
#include "SceneCamera.h"

#include "Galaxy/Core/Core.h"
#include "Galaxy/Core/Timestep.h"

namespace Galaxy
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(std::string tagName = "Default");
		void DestroyEntity(Entity entity);

		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);
	private:
		friend class Entity;
		friend class SceneHierarcyPanel;
		friend class SceneSerializer;

		Registry* m_Registry = new Registry();

		float m_ViewportWidth, m_ViewportHeight;
		//SceneCamera* m_SceneCamera;
	};
}