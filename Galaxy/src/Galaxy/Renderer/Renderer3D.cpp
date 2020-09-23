#include "gxpch.h"

#include "Galaxy/Core/Application.h"
#include "Platform/Windows/DirectXContext.h"

#include "Renderer3D.h"

#include "../vendor/DirectX/DDSTextureLoader.h"

#include <d3dcompiler.h>

#include <filesystem>

namespace Galaxy
{
	DirectXContext* Renderer3D::m_Context = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> Renderer3D::m_VertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> Renderer3D::m_IndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> Renderer3D::m_InputLayout = nullptr;

	Microsoft::WRL::ComPtr<ID3D11VertexShader> Renderer3D::m_VertexShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> Renderer3D::m_PixelShader = nullptr;

	Microsoft::WRL::ComPtr<ID3D11Buffer> Renderer3D::m_ConstantBuffer = nullptr;

	void Renderer3D::Init()
	{
		m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();

		HRESULT result;

		D3D11_BUFFER_DESC bDesc;
		ZeroMemory(&bDesc, sizeof(bDesc));

		bDesc.ByteWidth = sizeof(float) * 8;
		bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bDesc.CPUAccessFlags = 0;
		bDesc.StructureByteStride = 0;
		bDesc.MiscFlags = 0;
		bDesc.Usage = D3D11_USAGE_DEFAULT;

		float vertices[] =
		{
			-0.5f, -0.5f,
			-0.5f, 0.5f,
			0.5f, -0.5f,
			0.5f, 0.5f,
		};

		D3D11_SUBRESOURCE_DATA mData;
		ZeroMemory(&mData, sizeof(mData));

		mData.pSysMem = vertices;

		result = m_Context->GetDevice()->CreateBuffer(&bDesc, &mData, m_VertexBuffer.GetAddressOf());
		assert(!FAILED(result));

		ZeroMemory(&bDesc, sizeof(bDesc));
		bDesc.ByteWidth = sizeof(unsigned int) * 6;
		bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bDesc.CPUAccessFlags = 0;
		bDesc.MiscFlags = 0;
		bDesc.StructureByteStride = 0;
		bDesc.Usage = D3D11_USAGE_DEFAULT;

		unsigned int indices[]
		{
			0,1,2,
			1,3,2,
		};

		ZeroMemory(&mData, sizeof(mData));
		mData.pSysMem = indices;

		result = m_Context->GetDevice()->CreateBuffer(&bDesc, &mData, m_IndexBuffer.GetAddressOf());
		assert(!FAILED(result));

		D3D11_BUFFER_DESC cDesc;
		ZeroMemory(&cDesc, sizeof(cDesc));
		cDesc.ByteWidth = sizeof(float) * 8;
		cDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cDesc.CPUAccessFlags = 0;
		cDesc.MiscFlags = 0;
		cDesc.StructureByteStride = 0;
		cDesc.Usage = D3D11_USAGE_DEFAULT;

		result = m_Context->GetDevice()->CreateBuffer(&cDesc, nullptr, m_ConstantBuffer.GetAddressOf());
		assert(!FAILED(result));

		D3D11_INPUT_ELEMENT_DESC layout[]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		ID3D10Blob* vertexblob, * pixelblob;

		std::filesystem::path path = std::filesystem::current_path();

		std::wstring temp = path.relative_path().wstring();
		temp.append(L"\\src\\shaders\\VertexShader.hlsl");

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

		ID3D11Buffer* shapeBuffers[] = { m_VertexBuffer.Get() };
		UINT shapestrides[] = { sizeof(float) * 2 };
		UINT shapeoffsets[] = { 0 };

		m_Context->GetContext()->IASetVertexBuffers(0, 1, shapeBuffers, shapestrides, shapeoffsets);
		m_Context->GetContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_Context->GetContext()->VSSetShader(m_VertexShader.Get(), nullptr, 0);
		m_Context->GetContext()->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	}

	void Renderer3D::DrawQuad(float color[4])
	{
		m_Context->GetContext()->UpdateSubresource(m_ConstantBuffer.Get(), NULL, nullptr, color, 0, 0);

		ID3D11Buffer* constants = { m_ConstantBuffer.Get() };

		m_Context->GetContext()->PSSetConstantBuffers(0, 1, &constants);

		m_Context->GetContext()->DrawIndexed(6, 0, 0);

		m_Context->GetContext()->PSSetConstantBuffers(0, 0, nullptr);
	}
}