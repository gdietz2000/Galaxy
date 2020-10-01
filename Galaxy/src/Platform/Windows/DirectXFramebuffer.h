#pragma once

#include "Galaxy/Renderer/Renderer.h"
#include "Galaxy/Renderer/Framebuffer.h"

#include "Platform/Windows/DirectXContext.h"

#include <wrl.h>

namespace Galaxy
{
	class DirectXFramebuffer : public Framebuffer
	{
	public:
		DirectXFramebuffer(const FramebufferSpecification& specs);
		virtual ~DirectXFramebuffer() {}

		virtual void Bind() override;
		virtual void Unbind() override;

		void Invalidate();

		virtual void* Get() const { return m_FrameData.Get(); }
		virtual void** GetAddressOf() const { return (void**)m_FrameData.GetAddressOf(); }

		virtual void* GetImGuiDrawable() const override { return m_SRV.Get(); }
		virtual void** GetImGuiDrawableAddressOf() const override { return (void**)m_SRV.GetAddressOf(); }

		virtual void Reset() { m_FrameData.Reset(); }

		virtual const FramebufferSpecification& GetFramebufferSpecification() const override { return m_Specs; }

		virtual void Resize(uint32_t width, uint32_t height) override;

	private:
		DirectXContext* m_Context = nullptr;

		FramebufferSpecification m_Specs;
		bool defaultRenderTargetView = true;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_FrameData;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_CopyTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SRV;

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RTV;

	};
}