#include "gxpch.h"
#include "RenderCommand.h"

#include "Platform/Windows/DirectXRendererAPI.h"

namespace Galaxy
{
	RendererAPI* RenderCommand::s_RendererAPI = new DirectXRendererAPI();
}