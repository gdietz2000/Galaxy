#include "gxpch.h"

#include "DirectXTexture2D.h"
#include "Galaxy/Core/Application.h"

#include "../vendor/DirectX/DDSTextureLoader.h"

namespace Galaxy
{
	DirectXTexture2D::DirectXTexture2D(uint32_t width, uint32_t height)
	{
		m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();

		m_Width = width, m_Height = height;

		D3D11_TEXTURE2D_DESC tDesc;
		ZeroMemory(&tDesc, sizeof(tDesc));
		tDesc.ArraySize = 1;
		tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		tDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		tDesc.MipLevels = 1;
		tDesc.Usage = D3D11_USAGE_DEFAULT;
		tDesc.Width = m_Width;
		tDesc.Height = m_Height;
		tDesc.SampleDesc.Count = 1;

		HRESULT hr = m_Context->GetDevice()->CreateTexture2D(&tDesc, nullptr, m_Texture.GetAddressOf());
		assert(!FAILED(hr));

		D3D11_SHADER_RESOURCE_VIEW_DESC sDesc;
		ZeroMemory(&sDesc, sizeof(sDesc));
		sDesc.Format = tDesc.Format;
		sDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		sDesc.Texture2D.MipLevels = tDesc.MipLevels;
		sDesc.Texture2D.MostDetailedMip = 0;

		hr = m_Context->GetDevice()->CreateShaderResourceView(m_Texture.Get(), &sDesc, m_View.GetAddressOf());
		assert(!FAILED(hr));

		SetDesign(TextureMode::Wrap);
	}

	DirectXTexture2D::DirectXTexture2D(const std::string& filepath)
	{
		m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();

		std::wstring pathway = std::wstring(filepath.begin(), filepath.end());

		HRESULT hr = DirectX::CreateDDSTextureFromFile(m_Context->GetDevice().Get(), pathway.c_str(), (ID3D11Resource**)m_Texture.GetAddressOf(), m_View.GetAddressOf());
		assert(!FAILED(hr));

		D3D11_TEXTURE2D_DESC tempDesc;
		m_Texture->GetDesc(&tempDesc);

		m_Width = tempDesc.Width;
		m_Height = tempDesc.Height;

		SetDesign(TextureMode::Wrap);
	}

	void DirectXTexture2D::Bind(uint32_t index)
	{
		m_Index = index;

		m_Context->GetContext()->PSSetShaderResources(m_Index, 1, m_View.GetAddressOf());
		m_Context->GetContext()->PSSetSamplers(m_Index, 1, m_Sampler.GetAddressOf());
	}
	void DirectXTexture2D::Unbind() const
	{
		m_Context->GetContext()->PSSetShaderResources(m_Index, 0, nullptr);
		m_Context->GetContext()->PSSetSamplers(m_Index, 0, nullptr);
	}

	void DirectXTexture2D::SetDesign(TextureMode mode, glm::vec4 borderColor) const
	{
		D3D11_TEXTURE_ADDRESS_MODE textureMode;

		switch (mode)
		{
			case Texture::TextureMode::Wrap: textureMode = D3D11_TEXTURE_ADDRESS_WRAP; break;
			case Texture::TextureMode::Mirror: textureMode = D3D11_TEXTURE_ADDRESS_MIRROR; break;
			case Texture::TextureMode::Clamp: textureMode = D3D11_TEXTURE_ADDRESS_CLAMP; break;
			case Texture::TextureMode::Border: textureMode = D3D11_TEXTURE_ADDRESS_BORDER; break;
		}

		D3D11_SAMPLER_DESC sDesc;
		sDesc.AddressU = textureMode;
		sDesc.AddressV = textureMode;
		sDesc.AddressW = textureMode;

		sDesc.BorderColor[0] = borderColor.r;
		sDesc.BorderColor[1] = borderColor.g;
		sDesc.BorderColor[2] = borderColor.b;
		sDesc.BorderColor[3] = borderColor.a;

		sDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		sDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

		sDesc.MaxAnisotropy = 0;
		sDesc.MaxLOD = 1.0f;
		sDesc.MinLOD = 0.0f;
		sDesc.MipLODBias = 0;

		if (m_Sampler)
			m_Sampler->Release();

		HRESULT hr = m_Context->GetDevice()->CreateSamplerState(&sDesc, (ID3D11SamplerState**)m_Sampler.GetAddressOf());
		assert(!FAILED(hr));
	}

	void DirectXTexture2D::SetData(void* data, uint32_t size)
	{
		m_Context->GetContext()->UpdateSubresource(m_Texture.Get(), NULL, nullptr, data, 0, 0);
	}
}