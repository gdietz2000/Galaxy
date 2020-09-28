#include "gxpch.h"
#include "BatchArray.h"
#include "RendererAPI.h"

#include "Platform/Windows/DirectXBatchArray.h"

namespace Galaxy
{
	Ref<BatchArray> BatchArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: GX_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::API::DirectX: return CreateRef<DirectXBatchArray>();
		default:
			GX_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}
