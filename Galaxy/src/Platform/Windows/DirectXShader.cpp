#include "gxpch.h"
#include "Galaxy/Core/Application.h"
#include "DirectXShader.h"

#include <d3dcompiler.h>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Galaxy
{
	DirectXVertexShader::DirectXVertexShader(const std::string& filepath)
	{
		if (!m_Context)
			m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();

		D3D11_BUFFER_DESC cDesc;
		ZeroMemory(&cDesc, sizeof(cDesc));
		cDesc.ByteWidth = sizeof(float) * 100;
		cDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cDesc.CPUAccessFlags = 0;
		cDesc.MiscFlags = 0;
		cDesc.StructureByteStride = 0;
		cDesc.Usage = D3D11_USAGE_DEFAULT;

		for (size_t i = 0; i < 14; i++)
		{
			m_Context->GetDevice()->CreateBuffer(&cDesc, nullptr, m_ConstantBuffers[i].GetAddressOf());
		}

		D3DCompileFromFile(std::wstring(filepath.begin(), filepath.end()).c_str(), NULL, NULL, "main", "vs_4_0", D3DCOMPILE_DEBUG, 0, &m_Blob, nullptr);

		m_Context->GetDevice()->CreateVertexShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, m_VertexShader.GetAddressOf());
	}

	void DirectXVertexShader::SetMat4(const glm::mat4& matrix)
	{
		m_Context->GetContext()->UpdateSubresource(m_ConstantBuffers[m_UniformIndex].Get(), NULL, nullptr, glm::value_ptr(matrix), 0, 0);

		m_Context->GetContext()->VSSetConstantBuffers(m_UniformIndex, 1, m_ConstantBuffers[m_UniformIndex].GetAddressOf());
	}

	void DirectXVertexShader::Bind() const
	{
		m_Context->GetContext()->VSSetShader(m_VertexShader.Get(), nullptr, NULL);
	}

	void DirectXVertexShader::Unbind()
	{
		for (size_t i = 0; i < m_UniformIndex; i++)
		{
			m_Context->GetContext()->VSSetConstantBuffers(i, 1, nullptr);
		}

		m_UniformIndex = 0;

		m_Context->GetContext()->VSSetShader(nullptr, nullptr, NULL);
	}

	DirectXPixelShader::DirectXPixelShader(const std::string& filepath)
	{
		if (!m_Context)
			m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();

		D3DCompileFromFile(std::wstring(filepath.begin(), filepath.end()).c_str(), NULL, NULL, "main", "ps_4_0", D3DCOMPILE_DEBUG, 0, &m_Blob, nullptr);

		m_Context->GetDevice()->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, m_PixelShader.GetAddressOf());
	}

	void DirectXPixelShader::Bind() const
	{
		m_Context->GetContext()->PSSetShader(m_PixelShader.Get(), nullptr, NULL);
	}

	void DirectXPixelShader::Unbind()
	{
		m_Context->GetContext()->PSSetShader(nullptr, nullptr, NULL);
	}
}