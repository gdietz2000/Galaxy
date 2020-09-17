#include "gxpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_dx11.h"

#include "Galaxy/Core/Application.h"
#include "Platform/Windows/DirectXContext.h"

namespace Galaxy
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
		/*D3D_FEATURE_LEVEL dx11 = D3D_FEATURE_LEVEL_11_0;

		RECT rect;
		GetClientRect((HWND)Application::Get().GetWindow().GetNativeWindow(), &rect);

		DXGI_SWAP_CHAIN_DESC swapDesc;
		ZeroMemory(&swapDesc, sizeof(swapDesc));
		swapDesc.BufferCount = 1;
		swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapDesc.BufferDesc.Width = rect.right - rect.left;
		swapDesc.BufferDesc.Height = rect.bottom - rect.top;
		swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapDesc.OutputWindow = (HWND)Application::Get().GetWindow().GetNativeWindow();
		swapDesc.SampleDesc.Count = 1;
		swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapDesc.Windowed = true;

		D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG,
			&dx11, 1, D3D11_SDK_VERSION, &swapDesc, &swap, &device, nullptr, &context);

		ID3D11Resource* backbuffer;
		HRESULT hr = swap->GetBuffer(0, __uuidof(backbuffer), (void**)&backbuffer);
		hr = device->CreateRenderTargetView(backbuffer, NULL, &rtv);

		backbuffer->Release();

		context->OMSetRenderTargets(1, &rtv, nullptr);

		port.Width = swapDesc.BufferDesc.Width;
		port.Height = swapDesc.BufferDesc.Height;
		port.TopLeftX = port.TopLeftY = 0;
		port.MinDepth = 0; port.MaxDepth = 1;

		context->RSSetViewports(1, &port);*/
	}

	ImGuiLayer::~ImGuiLayer()
	{
		ImGui_ImplDX11_InvalidateDeviceObjects();
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();

		OnDetach();
	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplDX11_CreateDeviceObjects();
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender()
	{
		//float clearColor[4] = { 0.0f,1.0f,1.0f,1.0f };

		//auto graphics = (Graphics*)Application::Get().GetWindow().GetContext();
		//graphics->m_Context->ClearRenderTargetView(graphics->m_RenderTargetView, clearColor);
		//graphics->m_Context->OMSetRenderTargets(1, &graphics->m_RenderTargetView, nullptr);
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.m_Handled |= e.IsInCategory(CategoryMouse) & io.WantCaptureMouse;
			e.m_Handled |= e.IsInCategory(CategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		//Rendering
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}