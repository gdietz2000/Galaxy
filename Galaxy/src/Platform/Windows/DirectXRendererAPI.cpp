#include "gxpch.h"
#include "DirectXRendererAPI.h"

#include "Galaxy/Core/Application.h"
namespace Galaxy
{
	void DirectXRendererAPI::Init()
	{
		m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();
	}

	void DirectXRendererAPI::SetClearColor(float color[4])
	{
		memcpy_s(m_Color, sizeof(m_Color) * 4, color, sizeof(color) * 4);
	}

	void DirectXRendererAPI::Clear()
	{
		m_Context->GetContext()->ClearRenderTargetView(m_Context->GetRenderTargetView().Get(), m_Color);
	}
}