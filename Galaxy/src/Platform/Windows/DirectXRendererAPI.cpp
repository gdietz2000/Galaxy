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
		_r = color[0];
		_g = color[1];
		_b = color[2];
		_a = color[3];
	}

	void DirectXRendererAPI::Clear()
	{
		float m_Color[] = { _r, _g, _b, _a };
		m_Context->GetContext()->ClearRenderTargetView(m_Context->GetRenderTargetView().Get(), m_Color);
	}
}