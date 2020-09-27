#include "gxpch.h"
#include "Texture.h"
#include "RendererAPI.h"

#include "Platform/Windows/DirectXTexture2D.h"

namespace Galaxy
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: GX_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::API::DirectX: return CreateRef<DirectXTexture2D>(width, height);
		default:
			GX_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}

	Ref<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: GX_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::API::DirectX: return CreateRef<DirectXTexture2D>(filepath);
		default:
			GX_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}