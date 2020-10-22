#pragma once

#include <Galaxy.h>
#include "panels/SceneHierarchy.h"

namespace Galaxy
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& event) override;
		virtual void OnImGuiRender(Timestep ts) override;

	private:
		Ref<BatchArray> m_BatchArray;
		Ref<Shader> m_VertexShader;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;

		Galaxy::Entity m_CameraEntity;

		glm::vec4 m_SceneColor = {0.1f, 0.1f, 0.1f, 1.0f};

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		//Panels
		SceneHierarcyPanel m_SceneHierarcyPanel;
	};
}