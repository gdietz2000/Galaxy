#pragma once
#include "Galaxy/Renderer/Shader.h"
#include "Platform/Windows/DirectXContext.h"

#include <wrl.h>

namespace Galaxy
{
	namespace 
	{
		DirectXContext* m_Context;
	}

	class DirectXVertexShader : public Shader
	{
	public:
		DirectXVertexShader(const std::string& filepath);
		~DirectXVertexShader() {};

		virtual const std::string& GetName() const override { return m_Name; };

		virtual void* GetData() const override { return m_Blob->GetBufferPointer(); }
		virtual size_t GetSize() const override { return m_Blob->GetBufferSize(); }

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		Microsoft::WRL::ComPtr<ID3D10Blob> m_Blob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;

		std::string m_Name;
	};

	class DirectXPixelShader : public Shader
	{
	public:
		DirectXPixelShader(const std::string& filepath);
		~DirectXPixelShader() {};

		virtual const std::string& GetName() const override { return m_Name; }

		virtual void* GetData() const override { return m_Blob->GetBufferPointer(); }
		virtual size_t GetSize() const override { return m_Blob->GetBufferSize(); }

		virtual void Bind() const override;
		virtual void Unbind() const override;
 	private:
		Microsoft::WRL::ComPtr<ID3D10Blob> m_Blob;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;

		std::string m_Name;
	};
	
}