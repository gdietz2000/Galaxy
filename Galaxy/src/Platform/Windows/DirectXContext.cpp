#include "gxpch.h"
#include "DirectXContext.h"

#include "Galaxy/Core/Application.h"

#include <assert.h>
#include "WindowsWindow.h"
namespace Galaxy
{
	DirectXContext::DirectXContext(HWND* handle)
	{
		windowHandle = handle;
		m_Device = nullptr;
		m_Context = nullptr;
		m_SwapChain = nullptr;
		m_RenderTargetView = nullptr;
	}

	DirectXContext::~DirectXContext()
	{
		//if (m_SwapChain) m_SwapChain->Release();
		//if (m_RenderTargetView) m_RenderTargetView->Release();

		//if (m_Context) m_Context->Release();
		//if (m_Device) m_Device->Release();
	}

	void DirectXContext::Init()
	{
		D3D_FEATURE_LEVEL dx11 = D3D_FEATURE_LEVEL_11_0;

		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		RECT rect;
		::GetClientRect(*windowHandle, &rect);

		desc.BufferCount = 1;
		desc.BufferDesc.Width = rect.right - rect.left;
		desc.BufferDesc.Height = rect.bottom - rect.top;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		desc.OutputWindow = *windowHandle;
		desc.SampleDesc.Count = 1;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		desc.Windowed = true;

		HRESULT hr;

#ifdef _DEBUG
		hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, &dx11, 1, D3D11_SDK_VERSION, &desc, &m_SwapChain, &m_Device, nullptr, &m_Context);
#else
		hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, &dx11, 1, D3D11_SDK_VERSION, &desc, &m_SwapChain, &m_Device, nullptr, &m_Context);
#endif
		assert(!FAILED(hr));

		ID3D11Resource* backbuffer;
		hr = m_SwapChain->GetBuffer(0, __uuidof(backbuffer), (void**)&backbuffer);
		hr = m_Device->CreateRenderTargetView(backbuffer, NULL, &m_RenderTargetView);

		backbuffer->Release();

		ID3D11RenderTargetView* views = { m_RenderTargetView.Get() };

		m_Context->OMSetRenderTargets(1, &views, nullptr);
	}

	void DirectXContext::SwapBuffers()
	{
		bool vSync = Application::Get().GetWindow().IsVSync();
		m_SwapChain->Present(vSync, 0);
	}
}