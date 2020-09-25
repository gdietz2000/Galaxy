#pragma once
#include "Galaxy/Core/Application.h"

#include "glm/glm.hpp"

namespace Galaxy 
{
	class Renderer
	{
	public:
		static void Init();
		static void SetClearColor(const glm::vec4& color);
		static void Clear();
	};
}