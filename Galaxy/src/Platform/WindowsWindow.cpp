#include "gxpch.h"
#include "WindowsWindow.h"

#include "Galaxy/Events/ApplicationEvent.h"

namespace Galaxy
{
	WindowsWindow::WindowData WindowsWindow::m_Data;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}


	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	LRESULT CALLBACK WindowsWindow::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CLOSE:
		{
			WindowCloseEvent e;
			m_Data.EventCallback(e);
			PostQuitMessage(0);
			return 0;
		}
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.title = props.Title;
		m_Data.width = props.Width;
		m_Data.height = props.Height;

		WNDCLASSEX wcex;

		std::wstring ws, wsTemp = std::wstring(m_Data.title.begin(), m_Data.title.end());

		ws = wsTemp;

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WindowProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = NULL;
		wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszClassName = L"Galaxy App";
		wcex.lpszMenuName = ws.c_str();
		wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

		BOOL registered = RegisterClassEx(&wcex);

		if (!registered)
		{
			GX_CORE_FATAL("Failed to register windows window!");
			__debugbreak();
		}

		//m_Window = CreateWindow(wcex.lpszClassName, wcex.lpszMenuName, WS_OVERLAPPEDWINDOW, CW_DEFAULT, CW_DEFAULT, m_Data.width, m_Data.height, NULL, NULL, NULL, NULL);
		HWND m_Window = CreateWindow(L"Galaxy App", ws.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_Data.width, m_Data.height,	NULL, NULL,	NULL, NULL);

		if (m_Window == nullptr)
		{
			GX_CORE_FATAL("Failed to create Window!");
			__debugbreak();
		}

		ShowWindow(m_Window, SW_SHOW);
		UpdateWindow(m_Window);
	}

	void WindowsWindow::Shutdown()
	{
	
	}

	void WindowsWindow::OnUpdate()
	{
		MSG msg;
		if (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	void WindowsWindow::SetVSync(bool enabled)
	{
		m_Data.vSync = enabled;
	}

	bool WindowsWindow::IsVSync() const 
	{
		return m_Data.vSync;
	}
}