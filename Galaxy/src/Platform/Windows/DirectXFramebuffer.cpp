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
			HRESULT hr;

			//m_Context->GetRenderTargetView().Reset();
			//m_SRV.Reset();
			//m_Context->GetSwapChain()->ResizeBuffers(1, m_Specs.width, m_Specs.height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

			//HRESULT hr = m_Context->GetSwapChain()->GetBuffer(0, __uuidof((ID3D11Texture2D*)m_FrameData.Get()), (void**)m_FrameData.GetAddressOf());
			//hr = m_Context->GetDevice()->CreateRenderTargetView(m_FrameData.Get(), nullptr, m_Context->GetRenderTargetView().GetAddressOf());

			D3D11_TEXTURE2D_DESC tDesc;
			ZeroMemory(&tDesc, sizeof(tDesc));

			tDesc.ArraySize = 1;
			tDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			tDesc.CPUAccessFlags = 0;
			tDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			tDesc.Height = m_Specs.height;
			tDesc.MipLevels = 1;
			tDesc.SampleDesc.Count = 1;
			tDesc.Usage = D3D11_USAGE_DEFAULT;
			tDesc.Width = m_Specs.width;

			hr = m_Context->GetDevice()->CreateTexture2D(&tDesc, nullptr, m_CopyTexture.GetAddressOf());

			D3D11_SHADER_RESOURCE_VIEW_DESC sDesc;
			ZeroMemory(&sDesc, sizeof(sDesc));
			sDesc.Format = tDesc.Format;
			sDesc.Texture2D.MipLevels = tDesc.MipLevels;
			sDesc.Texture2D.MostDetailedMip = 0;
			sDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

			if (m_FrameData)
				m_FrameData.Reset();

			hr = m_Context->GetDevice()->CreateShaderResourceView(m_CopyTexture.Get(), &sDesc, m_FrameData.GetAddressOf());

			if (m_RenderTargetView)
				m_RenderTargetView.Reset();

			hr = m_Context->GetDevice()->CreateRenderTargetView(m_CopyTexture.Get(), nullptr, m_RenderTargetView.GetAddressOf());

			m_FrameTexture.Reset();
			m_CopyTexture.Reset();
		}
	}

	void DirectXFramebuffer::Bind()
	{
		defaultRenderTargetView = false;
		if (!m_Context)
			Invalidate();

		m_Context->GetContext()->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);
	}

	void DirectXFramebuffer::Unbind()
	{
		defaultRenderTargetView = true;
		m_Context->GetContext()->OMSetRenderTargets(1, m_Context->GetRenderTargetView().GetAddressOf(), nullptr);
	}

	void DirectXFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		m_Specs.width = width;
		m_Specs.height = height;

		if (m_Specs.width > 0 && m_Specs.height > 0)
			Invalidate();
	}
}