#include "gxpch.h"

#include "Galaxy/Core/Application.h"
#include "Platform/Windows/DirectXContext.h"

#include "Galaxy/Renderer/Buffer.h"

#include "Renderer3D.h"

#include "../vendor/DirectX/DDSTextureLoader.h"

#include "Galaxy/Renderer/Shader.h"

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

		Ref<Shader> vertexShader = Shader::Create("src/shaders/VertexShader.hlsl", Shader::ShaderType::Vertex);
		Ref<Shader> pixelShader = Shader::Create("src/shaders/PixelShader.hlsl", Shader::ShaderType::Pixel);

		result = m_Context->GetDevice()->CreateInputLayout(layout, 1, vertexShader->GetData(), vertexShader->GetSize(), m_InputLayout.GetAddressOf());
		assert(!FAILED(result));

		m_Context->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_Context->GetContext()->IASetInputLayout(m_InputLayout.Get());

		squareVertex->Bind();
		squareIndex->Bind();
		vertexShader->Bind();
		pixelShader->Bind();
	}

	void Renderer3D::DrawQuad(float color[4])
	{
		squareColor->SetData(color);

		squareColor->Bind(ConstantBuffer::ConstantBufferType::Pixel, 0);

		m_Context->GetContext()->DrawIndexed(6, 0, 0);

		squareColor->Unbind();
	}
}