#include "gxpch.h"

#include "Application.h"

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
	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		while (m_Running)
		{
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
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