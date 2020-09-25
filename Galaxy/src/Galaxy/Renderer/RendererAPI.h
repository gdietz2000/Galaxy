#pragma once

#include "glm/glm.hpp"

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

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}