#pragma once

#include "glm/glm.hpp"
#include "BatchArray.h"

namespace Galaxy
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			DirectX = 1
		};

	public:
		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const Ref<BatchArray>& batch, uint32_t indices) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}