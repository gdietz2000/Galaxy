#include "gxpch.h"
#include "Renderer.h"
#include "RenderCommand.h"
namespace Galaxy
{
	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::SetClearColor(float color[4]) 
	{
		RenderCommand::SetClearColor(color);
	}

	void Renderer::Clear()
	{
		RenderCommand::Clear();
	}

}