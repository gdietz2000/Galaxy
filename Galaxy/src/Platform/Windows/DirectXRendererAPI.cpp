#include "gxpch.h"
#include "DirectXRendererAPI.h"

#include "Galaxy/Core/Application.h"
#include "glm/gtc/type_ptr.hpp"

namespace Galaxy
{
	void DirectXRendererAPI::Init()
	{
		m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();
	}

	void DirectXRendererAPI::SetClearColor(const glm::vec4& color)
	{
		m_Color = color;
	}

	void DirectXRendererAPI::Clear()
	{
		m_Context->GetContext()->ClearRenderTargetView(m_Context->GetRenderTargetView().Get(), glm::value_ptr(m_Color));
	}
}