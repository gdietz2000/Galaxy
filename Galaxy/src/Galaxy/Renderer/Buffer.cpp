#include "gxpch.h"

#include "Buffer.h"
#include "Galaxy/Renderer/RendererAPI.h"
#include "Platform/Windows/DirectXBuffer.h"

namespace Galaxy
{
	Ref<InputLayout> InputLayout::Create(const BufferLayout& layout, Ref<Shader> vertexShader)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: GX_CORE_ASSERT(false, "Renderer does not support None"); return nullptr;
		case RendererAPI::API::DirectX: return CreateRef<DirectXInputLayout>(layout, vertexShader);
		default:
			GX_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: GX_CORE_ASSERT(false, "Renderer does not support None"); return nullptr;
		case RendererAPI::API::DirectX: return CreateRef<DirectXVertexBuffer>(vertices, size);
		default:
			GX_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: GX_CORE_ASSERT(false, "Renderer does not support None"); return nullptr;
		case RendererAPI::API::DirectX: return CreateRef<DirectXIndexBuffer>(indices, count);
		default:
			GX_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}

	Ref<ConstantBuffer> ConstantBuffer::Create(uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: GX_CORE_ASSERT(false, "Renderer does not support None"); return nullptr;
		case RendererAPI::API::DirectX: return CreateRef<DirectXConstantBuffer>(size);

		default:
			GX_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}
}