#pragma once

#include "Galaxy/Core/Core.h"
#include "Buffer.h"

namespace Galaxy
{
	class BatchArray
	{
	public:
		virtual ~BatchArray() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>&) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>&) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<BatchArray> Create();
	};
}