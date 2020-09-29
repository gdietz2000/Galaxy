#include "gxpch.h"

#include "Framebuffer.h"
#include "RendererAPI.h"

#include "Platform/Windows/DirectXFramebuffer.h"

namespace Galaxy
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specs)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: GX_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::API::DirectX: return CreateRef<DirectXFramebuffer>(specs);
		default:
			GX_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}