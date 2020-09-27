#pragma once

#include "gxpch.h"
#include "Galaxy/Core/Core.h"

namespace Galaxy
{
	class Texture
	{
	public:
		virtual ~Texture() {}

		virtual void Bind(uint32_t index = 0) = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& filepath);
	};
}