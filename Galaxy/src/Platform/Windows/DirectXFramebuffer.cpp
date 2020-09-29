#include "gxpch.h"
#include "DirectXFramebuffer.h"

namespace Galaxy
{
	static const uint32_t s_MaxFramebufferSize = 8192;

	DirectXFramebuffer::DirectXFramebuffer(const FramebufferSpecification& specs)
		: m_Specifications(specs)
	{
		Invalidate();
	}

	void DirectXFramebuffer::Invalidate()
	{
		
	}

	void DirectXFramebuffer::Bind()
	{
		
	}

	void DirectXFramebuffer::Unbind()
	{
	
	}

	void DirectXFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
		{
			GX_CORE_WARN("Attempted to resize frame buffer to {0} {1}", width, height);
			return;
		}

		m_Specifications.width = width;
		m_Specifications.height = height;

		Invalidate();
	}
}