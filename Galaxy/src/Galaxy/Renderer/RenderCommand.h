#pragma once

#include "RendererAPI.h"

namespace Galaxy
{
	class RenderCommand
	{
	public:
		inline static void Init() { s_RendererAPI->Init(); };
		inline static void SetClearColor(float color[4]) { s_RendererAPI->SetClearColor(color); };
		inline static void Clear() { s_RendererAPI->Clear(); };
	private:
		static RendererAPI* s_RendererAPI;
	};
}