#pragma once

#include "Platform/Windows/DirectXContext.h"
#include "Buffer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "wrl.h"

namespace Galaxy
{
	class Renderer3D
	{
	public:
		static void Init();
		//static void DrawQuad();
		static void DrawQuad(glm::vec4 color);
	private:
		static DirectXContext* m_Context;
	};
}