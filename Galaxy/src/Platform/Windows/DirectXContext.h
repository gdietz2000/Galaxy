#pragma once

#ifndef DirectXIncluded
#define DirectXIncluded
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <DirectXMath.h>
#endif

#include <wrl.h>
#include "Galaxy/Renderer/GraphicContext.h"

namespace Galaxy 
{
	class DirectXContext : public GraphicsContext
	{
	public:
		DirectXContext(HWND* handle);
		virtual ~DirectXContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;

		inline Microsoft::WRL::ComPtr<ID3D11Device>& GetDevice() { return m_Device; }
		inline Microsoft::WRL::ComPtr<ID3D11DeviceContext>& GetContext() { return m_Context; }
		inline Microsoft::WRL::ComPtr<IDXGISwapChain>& GetSwapChain() { return m_SwapChain; }
		inline Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& GetRenderTargetView() { return m_RenderTargetView; }
	private:
		HWND* windowHandle;

		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
	};
}