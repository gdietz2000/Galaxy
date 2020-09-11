#pragma once
#include "Galaxy/Renderer/RendererAPI.h"

namespace Galaxy
{
	class DirectXRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColor(float* color);
		virtual void Clear() override;
	};
}