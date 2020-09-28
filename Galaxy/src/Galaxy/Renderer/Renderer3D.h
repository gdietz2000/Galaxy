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
		static void Shutdown();

		static void BeginScene();
		static void EndScene();
		static void Flush();

		static void DrawQuad(glm::vec3 position, glm::vec4 color);

		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};

		static void ResetStats();
		static Statistics GetStats();
	private:
		static void FlushAndReset();

		static DirectXContext* m_Context;
	};
}