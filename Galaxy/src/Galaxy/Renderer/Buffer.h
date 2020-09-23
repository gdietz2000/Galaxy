#pragma once

#include "Galaxy/Core/Core.h"

namespace Galaxy
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};

		virtual void Bind(int index = 0) = 0;
		virtual void Unbind() const = 0;

		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};

	class ConstantBuffer
	{
	public:
		enum class ConstantBufferType
		{
			Vertex = 0,
			Pixel = 1,
			Geometry = 2,
			Compute = 3,
			Hull = 4,
			Domain = 5
		};
	public:
		virtual ~ConstantBuffer() {};

		virtual void SetData(void* data, uint32_t size = 0) const = 0;

		virtual void Bind(ConstantBufferType cbt, int index = 0) = 0;
		virtual void Unbind() const = 0;

		static Ref<ConstantBuffer> Create(uint32_t size);
	};
}