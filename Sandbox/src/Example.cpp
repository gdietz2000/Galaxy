#include "gxpch.h"
#include "Galaxy.h"
#include "ImGui/imgui.h"
#include "Galaxy/Events/ApplicationEvent.h"
#include "Galaxy/Renderer/Renderer.h"
#include "Galaxy/Renderer/Renderer3D.h"

#include "Galaxy/Core/Core.h"
#include "Galaxy/Renderer/Texture.h"

#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public Galaxy::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnAttach() override
	{
		m_SupernovaTexture = Galaxy::Texture2D::Create("src/textures/Supernova.dds");
	}

	void OnUpdate(Galaxy::Timestep ts) override 
	{
		Galaxy::Renderer3D::ResetStats();

		glm::vec4 color = { 0.0f,1.0f, 1.0f, 1.0f };
		Galaxy::Renderer::SetClearColor(color);
		Galaxy::Renderer::Clear();

		Galaxy::Renderer3D::BeginScene();

		Galaxy::Renderer3D::DrawQuad(glm::vec3(-0.5, 0.5, 0.0), m_Color);
		Galaxy::Renderer3D::DrawQuad(glm::vec3(-0.5, 0.0f, 0.0), glm::vec4(0, 0, 1, 1));

		Galaxy::Renderer3D::EndScene();
	}

	void OnImGuiRender(Galaxy::Timestep ts) override
	{
		ImGui::Begin("Frames Per Second");

		ImGui::Value("Draw Calls", Galaxy::Renderer3D::GetStats().DrawCalls);
		ImGui::Value("Quad Count", Galaxy::Renderer3D::GetStats().QuadCount);
		ImGui::Value("Total Vertex Count", Galaxy::Renderer3D::GetStats().GetTotalVertexCount());
		ImGui::Value("Total Index Count", Galaxy::Renderer3D::GetStats().GetTotalIndexCount());

		ImGui::ColorPicker4("Square Color", glm::value_ptr(m_Color));

		ImGui::End();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
private:
	glm::vec4 m_Color = {0.0f, 0.0f, 0.0f, 1.0f};
	Galaxy::Ref<Galaxy::Texture2D> m_SupernovaTexture;
};

class SandboxApp : public Galaxy::Application
{
public:
	SandboxApp() : Application("Supernova")
	{
		PushLayer(new ExampleLayer());
	}

	~SandboxApp()
	{
		
	}
};

Galaxy::Application* Galaxy::CreateApplication()
{
	return new SandboxApp();
}
