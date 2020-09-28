#include "gxpch.h"

#include "Galaxy/Core/Application.h"
#include "DirectXBuffer.h"

namespace Galaxy
{
	//Input Layout

	DirectXInputLayout::DirectXInputLayout(const BufferLayout& layout, Ref<Shader> vertexShader)
	{
		m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();

		m_Layout = layout;

		std::vector<D3D11_INPUT_ELEMENT_DESC> layoutVector;

		for (auto& element : m_Layout)
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

		m_Context->GetDevice()->CreateInputLayout(layoutVector.data(), layoutVector.size(), vertexShader->GetData(), vertexShader->GetSize(), m_InputLayout.GetAddressOf());
	}

	void DirectXInputLayout::Bind() const 
	{
		m_Context->GetContext()->IASetInputLayout(m_InputLayout.Get());
	}

	void DirectXInputLayout::Unbind() const
	{
		m_Context->GetContext()->IASetInputLayout(nullptr);
	}

	void DirectXInputLayout::SetTopology(const DrawType& drawType) const 
	{
		D3D11_PRIMITIVE_TOPOLOGY topology;

		switch (drawType)
		{
		case DrawType::Point: topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST; break;
		case DrawType::Line: topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST; break;
		case DrawType::Triangle: topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST; break;
		default:
			topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST; break;
		}

		m_Context->GetContext()->IASetPrimitiveTopology(topology);
	}

	//Vertex Buffer

	DirectXVertexBuffer::DirectXVertexBuffer(float* vertices, uint32_t size)
	{
		m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();

		D3D11_BUFFER_DESC bDesc;
		ZeroMemory(&bDesc, sizeof(bDesc));

		bDesc.ByteWidth = size;
		bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bDesc.CPUAccessFlags = 0;
		bDesc.MiscFlags = 0;
		bDesc.StructureByteStride = 0;
		bDesc.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA mData;
		ZeroMemory(&mData, sizeof(mData));

		mData.pSysMem = vertices;

		m_Context->GetDevice()->CreateBuffer(&bDesc, &mData, m_VertexBuffer.GetAddressOf());
	}

	void DirectXVertexBuffer::Bind(int index = 0)
	{
		ID3D11Buffer* buffers[] = { m_VertexBuffer.Get() };
		UINT strides[] = { sizeof(float) * 4 };
		UINT offset[] = { 0 };
		m_Context->GetContext()->IASetVertexBuffers(index, 1, buffers, strides, offset);
		m_Index = index;
	}

	void DirectXVertexBuffer::Unbind() const
	{
		m_Context->GetContext()->IASetVertexBuffers(m_Index, 0, nullptr, nullptr, nullptr);
	}

	//Index Buffer

	DirectXIndexBuffer::DirectXIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();

		D3D11_BUFFER_DESC bDesc;
		ZeroMemory(&bDesc, sizeof(bDesc));

		bDesc.ByteWidth = sizeof(uint32_t) * count;
		bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bDesc.CPUAccessFlags = 0;
		bDesc.MiscFlags = 0;
		bDesc.StructureByteStride = 0;
		bDesc.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA mData;
		ZeroMemory(&mData, sizeof(mData));

		mData.pSysMem = indices;

		m_Context->GetDevice()->CreateBuffer(&bDesc, &mData, m_IndexBuffer.GetAddressOf());
	}

	void DirectXIndexBuffer::Bind() const
	{
		m_Context->GetContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	void DirectXIndexBuffer::Unbind() const
	{
		m_Context->GetContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0);
	}

	//Constant Buffer
	DirectXConstantBuffer::DirectXConstantBuffer(uint32_t size)
	{
		m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();

		D3D11_BUFFER_DESC cDesc;
		ZeroMemory(&cDesc, sizeof(cDesc));
		cDesc.ByteWidth = size;
		cDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cDesc.CPUAccessFlags = 0;
		cDesc.MiscFlags = 0;
		cDesc.StructureByteStride = 0;
		cDesc.Usage = D3D11_USAGE_DEFAULT;

		m_Context->GetDevice()->CreateBuffer(&cDesc, nullptr, m_ConstantBuffer.GetAddressOf());

		m_BufferType = ConstantBufferType::Vertex;
		m_Index = 0;
	}

	void DirectXConstantBuffer::SetData(void* data, uint32_t size) const 
	{
		m_Context->GetContext()->UpdateSubresource(m_ConstantBuffer.Get(), NULL, nullptr, data, 0, 0);
	}

	void DirectXConstantBuffer::Bind(ConstantBufferType cbt, int index = 0)
	{
		m_BufferType = cbt;
		m_Index = index;

		switch (m_BufferType)
		{
		case Galaxy::ConstantBuffer::ConstantBufferType::Vertex:
			m_Context->GetContext()->VSSetConstantBuffers(index, 1, m_ConstantBuffer.GetAddressOf()); break;
		case Galaxy::ConstantBuffer::ConstantBufferType::Pixel:
			m_Context->GetContext()->PSSetConstantBuffers(index, 1, m_ConstantBuffer.GetAddressOf()); break;
		case Galaxy::ConstantBuffer::ConstantBufferType::Geometry:
			m_Context->GetContext()->GSSetConstantBuffers(index, 1, m_ConstantBuffer.GetAddressOf()); break;
		case Galaxy::ConstantBuffer::ConstantBufferType::Compute:
			m_Context->GetContext()->CSSetConstantBuffers(index, 1, m_ConstantBuffer.GetAddressOf()); break;
		case Galaxy::ConstantBuffer::ConstantBufferType::Hull:
			m_Context->GetContext()->HSSetConstantBuffers(index, 1, m_ConstantBuffer.GetAddressOf()); break;
		case Galaxy::ConstantBuffer::ConstantBufferType::Domain:
			m_Context->GetContext()->DSSetConstantBuffers(index, 1, m_ConstantBuffer.GetAddressOf()); break;
		}
	}

	void DirectXConstantBuffer::Unbind() const
	{
		switch (m_BufferType)
		{
		case Galaxy::ConstantBuffer::ConstantBufferType::Vertex:
			m_Context->GetContext()->VSSetConstantBuffers(m_Index, 0, nullptr); break;
		case Galaxy::ConstantBuffer::ConstantBufferType::Pixel:
			m_Context->GetContext()->PSSetConstantBuffers(m_Index, 0, nullptr); break;
		case Galaxy::ConstantBuffer::ConstantBufferType::Geometry:
			m_Context->GetContext()->GSSetConstantBuffers(m_Index, 0, nullptr); break;
		case Galaxy::ConstantBuffer::ConstantBufferType::Compute:
			m_Context->GetContext()->CSSetConstantBuffers(m_Index, 0, nullptr); break;
		case Galaxy::ConstantBuffer::ConstantBufferType::Hull:
			m_Context->GetContext()->HSSetConstantBuffers(m_Index, 0, nullptr); break;
		case Galaxy::ConstantBuffer::ConstantBufferType::Domain:
			m_Context->GetContext()->DSSetConstantBuffers(m_Index, 0, nullptr); break;
		}
	}
}