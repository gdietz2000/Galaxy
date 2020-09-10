#pragma once

#include "Core.h"
#include "Window.h"

namespace Galaxy
{
	class Application 
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();

		void OnEvent(Event& e);

		static inline Application* Get() { return s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:

		bool OnWindowClose(Event& e);
		

		Scope<Window> m_Window;
		bool m_Running = true;
		static Application* s_Instance;
	};

	Application* CreateApplication();
}