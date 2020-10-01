#include "EditorLayer.h"

#include "ImGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

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
		RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
		RenderCommand::Clear();

		m_Framebuffer->Bind();
		RenderCommand::SetClearColor(m_SceneColor);
		RenderCommand::Clear();

		m_ActiveScene->OnUpdate(ts);

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		
	}

	void EditorLayer::OnImGuiRender(Timestep ts)
	{
		ImGui::Begin("Settings");

		auto stats = Renderer3D::GetStats();
		ImGui::Text("Batch Renderer Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::Separator();

		ImGui::ColorPicker4("Scene Picker", glm::value_ptr(m_SceneColor));
		m_SceneColor.a = 1.0f;

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 1.0f, 1.0f });

		ImGui::Begin("DirectX11 Texture Test");

		ImVec2 regionAvailable = ImGui::GetContentRegionAvail();

		ImGui::Image((void*)m_Framebuffer->GetImGuiDrawable(), regionAvailable);
		ImGui::End();
		ImGui::PopStyleVar();
	}
}