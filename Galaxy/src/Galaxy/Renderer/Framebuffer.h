#pragma once

#include "Renderer.h"
#include "Galaxy/Core/Core.h"

namespace Galaxy
{
	struct FramebufferSpecification
	{
		uint32_t width, height;
		uint32_t samples = 1;

		bool swapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() {}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		virtual void* GetFrameData() = 0;
		virtual void** GetFrameDataAddress() = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& specs);

		virtual void Resize(uint32_t width, uint32_t height) = 0;
	};
}