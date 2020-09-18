#include "gxpch.h"
#include "Galaxy.h"
#include "ImGui/imgui.h"
#include "Galaxy/Events/ApplicationEvent.h"
#include "Galaxy/Renderer/Renderer.h"

class ExampleLayer : public Galaxy::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override 
	{
		float color[4] = { 0.0f,1.0f, 1.0f, 1.0f };
		Galaxy::Renderer::SetClearColor(color);

		Galaxy::Renderer::Clear();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Template");

		ImGui::End();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
};

class SandboxApp : public Galaxy::Application
{
public:
	SandboxApp()
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
