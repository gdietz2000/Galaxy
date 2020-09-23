#include "gxpch.h"

#include "Galaxy/Core/Application.h"
#include "Platform/Windows/DirectXContext.h"

#include "Galaxy/Renderer/Buffer.h"

#include "Renderer3D.h"

#include "../vendor/DirectX/DDSTextureLoader.h"

#include <d3dcompiler.h>

namespace Galaxy
{
	DirectXContext* Renderer3D::m_Context = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> Renderer3D::m_VertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> Renderer3D::m_IndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> Renderer3D::m_InputLayout = nullptr;

	Microsoft::WRL::ComPtr<ID3D11VertexShader> Renderer3D::m_VertexShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> Renderer3D::m_PixelShader = nullptr;

	Microsoft::WRL::ComPtr<ID3D11Buffer> Renderer3D::m_ConstantBuffer = nullptr;
	Ref<ConstantBuffer> Renderer3D::squareColor = nullptr;

	void Renderer3D::Init()
	{
		m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();

		HRESULT result;

		float vertices[] =
		{
			-0.5f, -0.5f,
			-0.5f, 0.5f,
			0.5f, -0.5f,
			0.5f, 0.5f,
		};

		unsigned int indices[]
		{
			0,1,2,
			1,3,2,
		};

		Ref<VertexBuffer> squareVertex = VertexBuffer::Create(vertices, sizeof(float) * 8);
		Ref<IndexBuffer> squareIndex = IndexBuffer::Create(indices, 6);
		squareColor = ConstantBuffer::Create(sizeof(float) * 4);

		D3D11_INPUT_ELEMENT_DESC layout[]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		ID3D10Blob* vertexblob, * pixelblob;
		result = D3DCompileFromFile(L"src/shaders/VertexShader.hlsl", NULL, NULL, "main", "vs_4_0", D3DCOMPILE_DEBUG, 0, &vertexblob, nullptr);
		assert(!FAILED(result));
		result = D3DCompileFromFile(L"src/shaders/PixelShader.hlsl", NULL, NULL, "main", "ps_4_0", D3DCOMPILE_DEBUG, 0, &pixelblob, nullptr);
		assert(!FAILED(result));

		result = m_Context->GetDevice()->CreateVertexShader(vertexblob->GetBufferPointer(), vertexblob->GetBufferSize(), nullptr, m_VertexShader.GetAddressOf());
		assert(!FAILED(result));
		result = m_Context->GetDevice()->CreatePixelShader(pixelblob->GetBufferPointer(), pixelblob->GetBufferSize(), nullptr, m_PixelShader.GetAddressOf());
		assert(!FAILED(result));

		result = m_Context->GetDevice()->CreateInputLayout(layout, 1, vertexblob->GetBufferPointer(), vertexblob->GetBufferSize(), m_InputLayout.GetAddressOf());
		assert(!FAILED(result));

		m_Context->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_Context->GetContext()->IASetInputLayout(m_InputLayout.Get());

		squareVertex->Bind();
		squareIndex->Bind();
		m_Context->GetContext()->VSSetShader(m_VertexShader.Get(), nullptr, 0);
		m_Context->GetContext()->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	}

	void Renderer3D::DrawQuad(float color[4])
	{
		squareColor->SetData(color);

		squareColor->Bind(ConstantBuffer::ConstantBufferType::Pixel, 0);

		m_Context->GetContext()->DrawIndexed(6, 0, 0);

		squareColor->Unbind();
	}
}