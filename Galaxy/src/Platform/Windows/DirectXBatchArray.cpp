#include "gxpch.h"
#include "DirectXBatchArray.h"

#include "Galaxy/Core/Application.h"

namespace Galaxy
{
	DirectXBatchArray::DirectXBatchArray()
	{
		m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();
	}

	void DirectXBatchArray::Bind() const
	{
		constexpr uint32_t MaxBuffers = 100;
		ID3D11Buffer* buffers[MaxBuffers];

		uint32_t index = 0;
		for(Ref<VertexBuffer> vb : m_VertexBuffers)
		{
			buffers[index++] = (ID3D11Buffer*)vb->GetData();
		}

		m_Context->GetContext()->IASetInputLayout(m_InputLayout.Get());
		m_Context->GetContext()->IASetVertexBuffers(0, m_VertexBuffers.size(), buffers, m_Strides.data(), m_Offsets.data());
		m_IndexBuffer->Bind();
	}

	void DirectXBatchArray::Unbind() const
	{
		ID3D11Buffer** buffers = nullptr;

		for (size_t i = 0; i < m_VertexBuffers.size(); i++)
		{
			buffers[i] = nullptr;
		}

		m_Context->GetContext()->IASetInputLayout(nullptr);
		m_Context->GetContext()->IASetVertexBuffers(0, m_VertexBuffers.size(), buffers, nullptr, nullptr);
		m_IndexBuffer->Unbind();
	}

	void DirectXBatchArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		const auto& layout = vertexBuffer->GetLayout();
		Ref<Shader> shader;
		if (m_InputLayout == nullptr)
		{
			shader = vertexBuffer->GetShader();
			std::vector<D3D11_INPUT_ELEMENT_DESC> layoutVector;

			for (auto& element : layout)
			{
				DXGI_FORMAT format;

				switch (element.Type)
				{
				case ShaderDataType::Float: format = DXGI_FORMAT_R32_FLOAT; break;
				case ShaderDataType::Float2: format = DXGI_FORMAT_R32G32_FLOAT; break;
				case ShaderDataType::Float3: format = DXGI_FORMAT_R32G32B32_FLOAT; break;
				case ShaderDataType::Float4: format = DXGI_FORMAT_R32G32B32A32_FLOAT; break;
				case ShaderDataType::Int: format = DXGI_FORMAT_R32_SINT; break;
				case ShaderDataType::Int2: format = DXGI_FORMAT_R32G32_SINT; break;
				case ShaderDataType::Int3: format = DXGI_FORMAT_R32G32B32_SINT; break;
				case ShaderDataType::Int4: format = DXGI_FORMAT_R32G32B32A32_SINT; break;
				case ShaderDataType::Mat3: format = DXGI_FORMAT_UNKNOWN; break;
				case ShaderDataType::Mat4: format = DXGI_FORMAT_UNKNOWN; break;
				case ShaderDataType::Bool: format = DXGI_FORMAT_R8_TYPELESS; break;
				}

				layoutVector.push_back({ element.Name.c_str(), 0, format, 0, element.Offset, D3D11_INPUT_PER_VERTEX_DATA, 0 });
			}

			m_Context->GetDevice()->CreateInputLayout(layoutVector.data(), layoutVector.size(), shader->GetData(), shader->GetSize(), m_InputLayout.GetAddressOf());
		}

		m_Strides.push_back(layout.GetStride());
		m_Offsets.push_back(0);

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void DirectXBatchArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		m_IndexBuffer = indexBuffer;
	}

	const std::vector<Ref<VertexBuffer>>& DirectXBatchArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const Ref<IndexBuffer>& DirectXBatchArray::GetIndexBuffer() const 
	{
		return m_IndexBuffer;
	}
}