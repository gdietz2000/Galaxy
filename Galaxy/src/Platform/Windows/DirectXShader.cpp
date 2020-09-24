#include "gxpch.h"
#include "Galaxy/Core/Application.h"
#include "DirectXShader.h"

#include <d3dcompiler.h>

namespace Galaxy
{
	DirectXVertexShader::DirectXVertexShader(const std::string& filepath)
	{
		if (!m_Context)
			m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();

		D3DCompileFromFile(std::wstring(filepath.begin(), filepath.end()).c_str(), NULL, NULL, "main", "vs_4_0", D3DCOMPILE_DEBUG, 0, &m_Blob, nullptr);

		m_Context->GetDevice()->CreateVertexShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, m_VertexShader.GetAddressOf());
	}

	void DirectXVertexShader::Bind() const
	{
		m_Context->GetContext()->VSSetShader(m_VertexShader.Get(), nullptr, NULL);
	}

	void DirectXVertexShader::Unbind() const
	{
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

	void DirectXPixelShader::Unbind() const
	{
		m_Context->GetContext()->PSSetShader(nullptr, nullptr, NULL);
	}
}