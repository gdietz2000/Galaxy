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
	struct Graphics 
	{
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_Context;
		IDXGISwapChain* m_SwapChain;
		ID3D11RenderTargetView* m_RenderTargetView;
	};

	class DirectXContext : public GraphicsContext
	{
	public:
		DirectXContext(HWND* handle);
		virtual ~DirectXContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;

		virtual void* Get() override;
	private:
		HWND* windowHandle;

		Graphics m_Gfx;
	};
}