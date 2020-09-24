#include "gxpch.h"
#include "Shader.h"

#include "RendererAPI.h"
#include "Platform/Windows/DirectXShader.h"

namespace Galaxy
{
	Ref<Shader> Shader::Create(const std::string& filepath, Shader::ShaderType st)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: GX_CORE_ASSERT(false, "Renderer does not support None."); nullptr;
		case RendererAPI::API::DirectX: 
			{
				switch (st)
				{
				case Galaxy::Shader::ShaderType::Vertex:
					return CreateRef<DirectXVertexShader>(filepath);
				case Galaxy::Shader::ShaderType::Pixel:
					return CreateRef<DirectXPixelShader>(filepath);
				case Galaxy::Shader::ShaderType::Geometry:
					return nullptr;
				case Galaxy::Shader::ShaderType::Compute:
					return nullptr;
				case Galaxy::Shader::ShaderType::Hull:
					return nullptr;
				case Galaxy::Shader::ShaderType::Domain:
					return nullptr;
				default:
					return nullptr;
				}
		
			}
		default:
			GX_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}
}