#pragma once

#include "Platform/Windows/DirectXContext.h"
#include "Galaxy/Renderer/BatchArray.h"

#include <wrl.h>

namespace Galaxy
{
	class DirectXBatchArray : public BatchArray
	{
	public:
		DirectXBatchArray();
		virtual ~DirectXBatchArray() {};

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override;
	private:
		DirectXContext* m_Context;

		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;

		std::vector<UINT> m_Strides;
		std::vector<UINT> m_Offsets;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}