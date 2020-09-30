#include "gxpch.h"

#include "Galaxy/Core/Application.h"
#include "Platform/Windows/DirectXContext.h"

#include "Galaxy/Renderer/Buffer.h"
#include "Galaxy/Renderer/BatchArray.h"
#include "RenderCommand.h"

#include "Renderer3D.h"

#include "Galaxy/Renderer/Shader.h"
#include "Galaxy/Renderer/Texture.h"

#include <d3dcompiler.h>

namespace Galaxy
{
	struct QuadVertex
	{
		glm::vec3 position;
		glm::vec2 texcoords;
		glm::vec4 color;
	};

	struct RenderData3D
	{
		static const uint32_t MaxQuads = 100000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<BatchArray> QuadBatchArray;
		Ref<VertexBuffer> QuadVertexBuffer;

		uint32_t QuadIndexCount = 0;

		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		Ref<Shader> m_VertexShader;
		Ref<Shader> m_ColorShader;

		Renderer3D::Statistics stats;

		glm::vec3 positions[4];
	};

	static RenderData3D data;

	void Renderer3D::Init()
	{
		HRESULT result;

		data.m_VertexShader = Shader::Create("assets/shaders/StandardVertexShader.hlsl", Shader::ShaderType::Vertex);

		data.QuadBatchArray = BatchArray::Create();

		data.QuadVertexBuffer = VertexBuffer::Create(data.MaxVertices * sizeof(QuadVertex));
		data.QuadVertexBuffer->SetLayout({
			{"POSITION", ShaderDataType::Float3},
			{"TEXCOORD", ShaderDataType::Float2},
			{"COLOR", ShaderDataType::Float4}
			}, data.m_VertexShader);

		data.QuadBatchArray->AddVertexBuffer(data.QuadVertexBuffer);

		data.QuadVertexBufferBase = new QuadVertex[data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < RenderData3D::MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> QuadIndexBuffer = IndexBuffer::Create(quadIndices, data.MaxIndices);
		data.QuadBatchArray->SetIndexBuffer(QuadIndexBuffer);
		delete[] quadIndices;

		data.m_ColorShader = Shader::Create("assets/shaders/StandardPixelShader.hlsl", Shader::ShaderType::Pixel);
		data.m_ColorShader->Bind();

		data.positions[0] = { -0.5f, -0.5f, 0.0f };
		data.positions[1] = { 0.5f, -0.5f, 0.0f };
		data.positions[2] = { 0.5f, 0.5f, 0.0f };
		data.positions[3] = { -0.5f, 0.5f, 0.0f };
	}

	void Renderer3D::Shutdown()
	{
		delete[] data.QuadVertexBufferBase;
	}

	void Renderer3D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		glm::mat4 viewProj = camera.GetProjection() * glm::inverse(transform);

		data.QuadBatchArray->Bind();
		data.m_VertexShader->Bind();
		data.m_VertexShader->SetMat4(viewProj);
		
		data.m_ColorShader->Bind();

		data.QuadIndexCount = 0;
		data.QuadVertexBufferPtr = data.QuadVertexBufferBase;
	}

	void Renderer3D::EndScene()
	{
		uint32_t dataSize = (uint32_t)((uint8_t*)data.QuadVertexBufferPtr - (uint8_t*)data.QuadVertexBufferBase);
		data.QuadVertexBuffer->SetData(data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer3D::Flush()
	{
		if (data.QuadIndexCount == 0)
			return;

		RenderCommand::DrawIndexed(data.QuadBatchArray, data.QuadIndexCount);
		data.stats.DrawCalls++;
	}

	void Renderer3D::FlushAndReset()
	{
		EndScene();

		data.QuadIndexCount = 0;
		data.QuadVertexBufferPtr = data.QuadVertexBufferBase;

	}

	void Renderer3D::DrawQuad(glm::vec3 position, glm::vec4 color)
	{
		constexpr size_t quadVertexCount = 4;

		glm::vec2 texcoords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };

		if (data.QuadIndexCount >= RenderData3D::MaxIndices)
			FlushAndReset();

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			data.QuadVertexBufferPtr->position = data.positions[i] + position;
			data.QuadVertexBufferPtr->texcoords = texcoords[i];
			data.QuadVertexBufferPtr->color = color;
			data.QuadVertexBufferPtr++;
		}

		data.QuadIndexCount += 6;

		data.stats.QuadCount++;
	}

	void Renderer3D::ResetStats()
	{
		memset(&data.stats, 0, sizeof(Statistics));
	}

	Renderer3D::Statistics Renderer3D::GetStats()
	{
		return data.stats;
	}
}