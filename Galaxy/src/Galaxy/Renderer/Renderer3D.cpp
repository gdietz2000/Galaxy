#include "gxpch.h"

#include "Galaxy/Core/Application.h"
#include "Platform/Windows/DirectXContext.h"

#include "Galaxy/Renderer/Buffer.h"

#include "Renderer3D.h"

#include "Galaxy/Renderer/Shader.h"
#include "Galaxy/Renderer/Texture.h"

#include <d3dcompiler.h>

namespace Galaxy
{
	DirectXContext* Renderer3D::m_Context = nullptr;

	struct RenderData3D
	{
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
		Ref<InputLayout> m_InputLayout;

		Ref<Shader> m_VertexShader;
		Ref<Shader> m_PixelShader;

		Ref<ConstantBuffer> m_ColorBuffer;

		Ref<Texture2D> m_WhiteTexture;
	};

	static RenderData3D data;

	void Renderer3D::Init()
	{
		m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();

		HRESULT result;

		float vertices[] =
		{
			-1, -1, 0.0f, 1.0f,
			-1, 1, 0.0f, 0.0f,
			1, -1, 1.0f, 1.0f,
			1, 1, 1.0f, 0.0f,
		};

		unsigned int indices[]
		{
			0,1,2,
			1,3,2,
		};

		data.m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(float) * 16);
		data.m_IndexBuffer = IndexBuffer::Create(indices, 6);
		data.m_ColorBuffer = ConstantBuffer::Create(sizeof(float) * 4);

		data.m_VertexShader = Shader::Create("src/shaders/VertexShader.hlsl", Shader::ShaderType::Vertex);
		//data.m_PixelShader = Shader::Create("src/shaders/PixelShader.hlsl", Shader::ShaderType::Pixel);
		data.m_PixelShader = Shader::Create("src/shaders/TextureShader.hlsl", Shader::ShaderType::Pixel);

		data.m_InputLayout = InputLayout::Create(
			{ 
				{std::string("POSITION"), ShaderDataType::Float2 },
				{std::string("TEXCOORD"), ShaderDataType::Float2 }
			}, data.m_VertexShader);
		
		data.m_InputLayout->SetTopology(DrawType::Triangle);


		data.m_WhiteTexture = Texture2D::Create("src/textures/Supernova.dds");
		
		//data.m_WhiteTexture = Texture2D::Create(1, 1);
		//uint32_t textureData = 0xffffffff;
		//data.m_WhiteTexture->SetData(&textureData, sizeof(uint32_t));
	}

	void Renderer3D::DrawQuad(glm::vec4 color)
	{
		data.m_VertexBuffer->Bind();
		data.m_IndexBuffer->Bind();
		data.m_InputLayout->Bind();

		data.m_VertexShader->Bind();
		data.m_PixelShader->Bind();

		//Set Color to ImGui value
		//data.m_ColorBuffer->SetData((glm::vec4*)&color);
		//data.m_ColorBuffer->Bind(ConstantBuffer::ConstantBufferType::Pixel, 0);

		data.m_WhiteTexture->Bind();

		//Draw the thing
		m_Context->GetContext()->DrawIndexed(6, 0, 0);

		//Unbind current buffer
		data.m_VertexBuffer->Unbind();
		data.m_IndexBuffer->Unbind();
		data.m_InputLayout->Unbind();

		data.m_VertexShader->Unbind();
		data.m_PixelShader->Unbind();

		//data.m_ColorBuffer->Unbind();
	}
}