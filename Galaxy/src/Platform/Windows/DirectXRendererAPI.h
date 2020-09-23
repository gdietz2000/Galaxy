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
		virtual void SetClearColor(float color[4]) override;
		virtual void Clear() override;

	private:
		DirectXContext* m_Context;
		float _r, _g, _b, _a;
	};
}