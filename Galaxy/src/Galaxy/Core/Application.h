#pragma once

#include "Core.h"

#include "Timestep.h"

#include "Window.h"
#include "LayerStack.h"
#include "Galaxy/ImGui/ImGuiLayer.h"
#include "Galaxy/Events/ApplicationEvent.h"

#include <chrono>

namespace Galaxy
{
	class Application 
	{
	public:
		Application(const std::string& title = "Galaxy Engine", uint32_t width = 1280, uint32_t height = 720);
		virtual ~Application();

		virtual void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		
		float m_DeltaTime;
		std::chrono::steady_clock::time_point lastUpdate;

		Scope<Window> m_Window;
		bool m_Running = true;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		static Application* s_Instance;
	};

	Application* CreateApplication();
}