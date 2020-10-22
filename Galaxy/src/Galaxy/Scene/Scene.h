#pragma once

#include "Managers.h"
#include "SceneCamera.h"
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
		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);
	private:
		friend class Entity;
		friend class SceneHierarcyPanel;

		Registry* m_Registry = new Registry();
		SceneCamera* m_SceneCamera;
	};
}