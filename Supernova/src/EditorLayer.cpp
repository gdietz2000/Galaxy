#include "EditorLayer.h"

namespace Galaxy
{
	EditorLayer::EditorLayer()
		: Layer("EditorLayer")
	{
		
	}

	EditorLayer::~EditorLayer()
	{
		
	}

	void EditorLayer::OnAttach()
	{
		FramebufferSpecification fbSpecs;
		fbSpecs.width = Application::Get().GetWindow().GetWidth();
		fbSpecs.height = Application::Get().GetWindow().GetHeight();

		m_Framebuffer = Application::Get().GetWindow().GetFramebuffer();

		m_ActiveScene = CreateRef<Scene>();
	}

	void EditorLayer::OnDetach()
	{
	
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		Renderer3D::ResetStats();
		m_Framebuffer->Bind();

		RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
		RenderCommand::Clear();

		m_ActiveScene->OnUpdate(ts);

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		
	}

	void EditorLayer::OnImGuiRender(Timestep ts)
	{
		
	}
}