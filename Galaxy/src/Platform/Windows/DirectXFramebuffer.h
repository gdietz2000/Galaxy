#pragma once

#include <wrl.h>
#include "Galaxy/Renderer/Framebuffer.h"

namespace Galaxy
{
	class DirectXFramebuffer : public Framebuffer
	{
	public:
		DirectXFramebuffer(const FramebufferSpecification& specs);
		virtual ~DirectXFramebuffer() {};

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void* GetFrameData() override { return m_FrameData.Get(); };
		virtual void** GetFrameDataAddress() override { return (void**)m_FrameData.GetAddressOf(); };

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specifications; };

		virtual void Resize(uint32_t width, uint32_t height) override;

		void Invalidate();
	private:
		FramebufferSpecification m_Specifications;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_FrameData;
	};
}