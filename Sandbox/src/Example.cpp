#include "gxpch.h"
#include "Galaxy.h"
#include "ImGui/imgui.h"
#include "Galaxy/Events/ApplicationEvent.h"
#include "Galaxy/Renderer/Renderer.h"
#include "Galaxy/Renderer/Renderer3D.h"

#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public Galaxy::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate(Galaxy::Timestep ts) override 
	{
		glm::vec4 color = { 0.0f,1.0f, 1.0f, 1.0f };
		Galaxy::Renderer::SetClearColor(color);
		Galaxy::Renderer::Clear();

		Galaxy::Renderer3D::DrawQuad(m_Color);
	}

	void OnImGuiRender(Galaxy::Timestep ts) override
	{
		ImGui::Begin("Frames Per Second");

		ImGui::Value("FPS", 1.0f / ts.GetSeconds());

		ImGui::ColorPicker4("Square Color", glm::value_ptr(m_Color));

		ImGui::End();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
private:
	glm::vec4 m_Color = {0.0f, 0.0f, 0.0f, 1.0f};
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
