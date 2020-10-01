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
		ID3D11RenderTargetView* views[1];
		m_Context->GetContext()->OMGetRenderTargets(1, views, nullptr);

		if (views[0] == nullptr)
			m_Context->GetContext()->ClearRenderTargetView(m_Context->GetRenderTargetView().Get(), glm::value_ptr(m_Color));
		else
			m_Context->GetContext()->ClearRenderTargetView(views[0], glm::value_ptr(m_Color));

		if (views[0] != nullptr)
			views[0]->Release();
	}

	void DirectXRendererAPI::DrawIndexed(const Ref<BatchArray>& batch, uint32_t indices)
	{
		uint32_t count = indices ? indices : batch->GetIndexBuffer()->GetCount();
		m_Context->GetContext()->DrawIndexed(count, 0, 0);
	}
}