#pragma once

#include "RendererAPI.h"

#include "glm/glm.hpp"

namespace Galaxy
{
	class RenderCommand
	{
	public:
		inline static void Init() { s_RendererAPI->Init(); };
		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); };
		inline static void Clear() { s_RendererAPI->Clear(); };
		inline static void DrawIndexed(const Ref<BatchArray>& batch, uint32_t indices) { s_RendererAPI->DrawIndexed(batch, indices); }
	private:
		static RendererAPI* s_RendererAPI;
	};
}