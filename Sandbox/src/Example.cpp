#include "gxpch.h"
#include "Galaxy.h"
#include "ImGui/imgui.h"
#include "Galaxy/Events/ApplicationEvent.h"
#include "Galaxy/Renderer/Renderer.h"
#include "Galaxy/Renderer/Renderer3D.h"

class ExampleLayer : public Galaxy::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate(Galaxy::Timestep ts) override 
	{
		float color[4] = { 0.0f,1.0f, 1.0f, 1.0f };
		Galaxy::Renderer::SetClearColor(color);
		Galaxy::Renderer::Clear();

		Galaxy::Renderer3D::DrawQuad(m_Color);
	}

	void OnImGuiRender(Galaxy::Timestep ts) override
	{
		ImGui::Begin("Frames Per Second");

		ImGui::Value("FPS", 1.0f / ts.GetSeconds());

		ImGui::ColorPicker4("Square Color", m_Color);

		ImGui::End();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
private:
	float m_Color[4] = { 0,0,0,0 };
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
