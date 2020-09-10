#include "gxpch.h"
#include "Galaxy.h"
#include "Galaxy/Events/ApplicationEvent.h"

class ExampleLayer : public Galaxy::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override 
	{
		//GX_INFO("ExampleLayer::Update");
	}

	void OnEvent(Galaxy::Event& e) override
	{
		//GX_TRACE("{0}", e.ToString());
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
