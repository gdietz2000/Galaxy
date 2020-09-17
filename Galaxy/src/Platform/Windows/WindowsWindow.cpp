#include "gxpch.h"
#include "WindowsWindow.h"

#include "Galaxy/Events/ApplicationEvent.h"
#include "Galaxy/Events/KeyEvent.h"
#include "Galaxy/Events/MouseEvent.h"

#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_dx11.h"
#include "Platform/Windows/DirectXContext.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Galaxy
{

	WindowsWindow::WindowData WindowsWindow::m_Data;

	GraphicsContext* WindowsWindow::m_Context = nullptr;

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
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		switch (msg)
		{
		//Window Close
		case WM_CLOSE:
		{
			WindowCloseEvent e;
			m_Data.EventCallback(e);
			PostQuitMessage(0);
			return 0;
		}

		//Mouse Button Events
		case WM_LBUTTONDOWN:
		{
			MouseButtonPressedEvent e(0);
			m_Data.EventCallback(e);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			MouseButtonReleasedEvent e(0);
			m_Data.EventCallback(e);
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			MouseButtonPressedEvent e(1);
			m_Data.EventCallback(e);
			return 0;
		}
		case WM_RBUTTONUP:
		{
			MouseButtonReleasedEvent e(1);
			m_Data.EventCallback(e);
			return 0;
		}
		case WM_MBUTTONDOWN:
		{
			MouseButtonPressedEvent e(2);
			m_Data.EventCallback(e);
			return 0;
		}
		case WM_MBUTTONUP:
		{
			MouseButtonReleasedEvent e(2);
			m_Data.EventCallback(e);
			return 0;
		}

		//Key Events
		case WM_KEYDOWN:
		{
			KeyPressedEvent e(wParam, lParam);
			m_Data.EventCallback(e);
			return 0;
		}
		case WM_KEYUP:
		{
			KeyReleasedEvent e(wParam);
			m_Data.EventCallback(e);
			return 0;
		}
		case WM_CHAR:
		{
			KeyTypedEvent e(wParam);
			m_Data.EventCallback(e);
			return 0;
		}
		//TODO: Mouse Position


		//Window Resize
		case WM_SIZE:
		{
			//Needed for ImGui Resizing-----------------------
			UINT width = LOWORD(lParam);
			UINT height = HIWORD(lParam);

			//auto& graphics = *(Graphics*)m_Context->Get();

			//graphics.m_RenderTargetView->Release();

			//graphics.m_SwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

			//ID3D11Resource* backbuffer;
			//HRESULT hr = graphics.m_SwapChain->GetBuffer(0, __uuidof(backbuffer), (void**)&backbuffer);
			//hr = graphics.m_Device->CreateRenderTargetView(backbuffer, NULL, &graphics.m_RenderTargetView);

			//backbuffer->Release();
			//------------------------------------------------

			m_Data.width = width;
			m_Data.height = height;

			WindowResizeEvent e(m_Data.width, m_Data.height);
			if (m_Data.EventCallback) m_Data.EventCallback(e);
			break;
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

		m_Window = CreateWindow(L"Galaxy App", ws.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_Data.width, m_Data.height,	NULL, NULL,	NULL, NULL);

		if (m_Window == nullptr)
		{
			GX_CORE_FATAL("Failed to create Window!");
			__debugbreak();
		}

		m_Context = new DirectXContext(&m_Window);
		m_Context->Init();

		auto graphics = *(Graphics*)m_Context->Get();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(m_Window);
		ImGui_ImplDX11_Init(graphics.m_Device, graphics.m_Context);

		ShowWindow(m_Window, SW_SHOW);
		UpdateWindow(m_Window);
	}

	void WindowsWindow::Shutdown()
	{
		delete m_Context;
	}

	void WindowsWindow::OnUpdate()
	{
		MSG msg;

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		m_Context->SwapBuffers();

		auto graphics = *(Graphics*)m_Context->Get();

		float color[] = { 0.0f,1.0f,1.0f,1.0f };

		graphics.m_Context->ClearRenderTargetView(graphics.m_RenderTargetView, color);
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