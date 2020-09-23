#include "gxpch.h"

#include "Application.h"
#include "Galaxy/Renderer/Renderer.h"
#include "Galaxy/Renderer/Renderer3D.h"
#include "Galaxy/ImGui/ImGuiLayer.h"

namespace Galaxy 
{
	Application* Application::s_Instance;

	Application::Application()
	{
		if (!s_Instance)
			s_Instance = this;

		GX_CORE_INFO("Application Created");
		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(GX_BIND(Application::OnEvent));

		Renderer::Init();
		Renderer3D::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);
	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		while (m_Running)
		{

			auto now = std::chrono::high_resolution_clock::now();
			Timestep ts = std::chrono::duration<float>(now - lastUpdate).count();
			lastUpdate = now;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(ts);

			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender(ts);

			m_ImGuiLayer->End();

			m_Window->OnUpdate(ts);
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GX_BIND(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(GX_BIND(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.m_Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return false;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		GX_CORE_INFO(e.ToString());
		return false;
	}
}