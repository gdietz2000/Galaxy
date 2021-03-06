#include "gxpch.h"
#include "Renderer.h"
#include "RenderCommand.h"
namespace Galaxy
{
	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::SetClearColor(const glm::vec4& color) 
	{
		RenderCommand::SetClearColor(color);
	}

	void Renderer::Clear()
	{
		RenderCommand::Clear();
	}

}