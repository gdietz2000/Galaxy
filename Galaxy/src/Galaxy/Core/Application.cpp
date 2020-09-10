#include "gxpch.h"

#include "Application.h"
#include "Galaxy/Events/ApplicationEvent.h"
#include "Core.h"

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
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GX_BIND(Application::OnWindowClose));
	}

	bool Application::OnWindowClose(Event& e)
	{
		m_Running = false;
		return false;
	}
}