#pragma once
#include "Galaxy/Core/Window.h"
#include "Galaxy/Renderer/Renderer.h"
#include "Platform/Windows/DirectXContext.h"
namespace Galaxy
{
	class WindowsWindow : public Window
	{
		friend class Renderer;
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate(Timestep ts) override;

		inline uint32_t GetWidth() const { return m_Data.width; }
		inline uint32_t GetHeight() const { return m_Data.height; }

		inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
		inline virtual void* GetContext() const { return m_Context; }
	private:
		void Init(const WindowProps& props);
		void Shutdown();

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		HWND m_Window;
		static DirectXContext* m_Context;

		struct WindowData
		{
			std::string title;
			uint32_t width, height;
			bool vSync;

			EventCallbackFn EventCallback;
		};

		static WindowData m_Data;
	};
}