#pragma once

#include "Galaxy/Core/Core.h"
#include "Galaxy/Scene/Scene.h"
#include "Galaxy/Scene/Entity.h"

namespace Galaxy
{
	class SceneHierarcyPanel
	{
	public:
		SceneHierarcyPanel() = default;
		SceneHierarcyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;

		Entity m_SelectionContext;
	};
}