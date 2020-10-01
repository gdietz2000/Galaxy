#include "gxpch.h"

#include "DirectXFramebuffer.h"
#include "Galaxy/Core/Application.h"

namespace Galaxy
{
	DirectXFramebuffer::DirectXFramebuffer(const FramebufferSpecification& specs)
		: m_Specs(specs)
	{
		Window& window = Application::Get().GetWindow();

		if (window)
			if (window.GetContext())
				m_Context = (DirectXContext*)window.GetContext();

		Invalidate();
	}

	void DirectXFramebuffer::Invalidate()
	{
		if (!m_Context)
		{
			Window& window = Application::Get().GetWindow();
			if (window)
				if (window.GetContext())
					m_Context = (DirectXContext*)window.GetContext();
		}
		
		if (m_Context)
		{
			m_Context->GetRenderTargetView().Reset();
			m_Context->GetSwapChain()->ResizeBuffers(1, m_Specs.width, m_Specs.height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

			HRESULT hr = m_Context->GetSwapChain()->GetBuffer(0, __uuidof((ID3D11Texture2D*)m_FrameData.Get()), (void**)m_FrameData.GetAddressOf());
			hr = m_Context->GetDevice()->CreateRenderTargetView(m_FrameData.Get(), nullptr, m_Context->GetRenderTargetView().GetAddressOf());

			m_FrameData.Reset();

			m_Context->GetContext()->OMSetRenderTargets(1, m_Context->GetRenderTargetView().GetAddressOf(), nullptr);
		}
	}

	void DirectXFramebuffer::Bind()
	{

	}

	void DirectXFramebuffer::Unbind()
	{
	}

	void DirectXFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		m_Specs.width = width;
		m_Specs.height = height;

		Invalidate();
	}
}