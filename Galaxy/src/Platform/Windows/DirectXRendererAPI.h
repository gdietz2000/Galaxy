#pragma once

#include "Platform/Windows/DirectXContext.h"
#include "Galaxy/Renderer/RendererAPI.h"

#include <wrl.h>

namespace Galaxy
{
	class DirectXRendererAPI : public RendererAPI
	{
	public:

		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const Ref<BatchArray>& batch, uint32_t indices) override;

	private:
		DirectXContext* m_Context;
		glm::vec4 m_Color;
	};
}