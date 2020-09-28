#pragma once

#include "Platform/Windows/DirectXContext.h"
#include "Galaxy/Renderer/Buffer.h"

#include <wrl.h>

namespace Galaxy
{

	class DirectXVertexBuffer : public VertexBuffer
	{
	public:
		DirectXVertexBuffer(float* vertices, uint32_t size);
		DirectXVertexBuffer(uint32_t size);
		virtual ~DirectXVertexBuffer() {};

		virtual void SetTopology(const DrawType& drawType) const override;
		virtual const BufferLayout& GetLayout() const override;
		virtual const Ref<Shader>& GetShader() const override;
		virtual void SetLayout(const BufferLayout& layout, Ref<Shader> vertexShader) override;

		virtual void SetData(void* data, uint32_t size) override;
		virtual void* GetData() const override { return m_VertexBuffer.Get(); }

		virtual void Bind(int index) override;
		virtual void Unbind() const override;

	private:
		DirectXContext* m_Context;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;

		BufferLayout m_Layout;
		Ref<Shader> m_VertexShaderRef;


		int m_Index = 0;
	};

	class DirectXIndexBuffer : public IndexBuffer
	{
	public:
		DirectXIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~DirectXIndexBuffer() {};

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline virtual uint32_t GetCount() const override { return m_Count; }
	private:
		DirectXContext* m_Context;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;

		uint32_t m_Count;
	};

	class DirectXConstantBuffer : public ConstantBuffer
	{
	public:
		DirectXConstantBuffer(uint32_t size);
		virtual ~DirectXConstantBuffer() {};

		//If on Windows size is not needed, value passed in will not be used
		virtual void SetData(void* data, uint32_t size = 0) const override;

		virtual void Bind(ConstantBufferType cbt, int index) override;
		virtual void Unbind() const override;
	private:
		DirectXContext* m_Context;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_ConstantBuffer;

		ConstantBufferType m_BufferType;
		int m_Index;
	};
}