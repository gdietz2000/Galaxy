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
		tDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
		tDesc.ArraySize = 1;
		tDesc.MipLevels = 0;
		tDesc.Usage = D3D11_USAGE_DEFAULT;
		tDesc.Width = m_Width;
		tDesc.Height = m_Height;
		tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		tDesc.SampleDesc.Count = 1;

		HRESULT hr = m_Context->GetDevice()->CreateTexture2D(&tDesc, nullptr, m_Texture.GetAddressOf());
		assert(!FAILED(hr));
	}

	DirectXTexture2D::DirectXTexture2D(const std::string& filepath)
	{
		m_Context = (DirectXContext*)Application::Get().GetWindow().GetContext();

		HRESULT hr = DirectX::CreateDDSTextureFromFile(m_Context->GetDevice().Get(), std::wstring(filepath.begin(), filepath.end()).c_str(), (ID3D11Resource**)m_Texture.GetAddressOf(), nullptr);
		assert(!FAILED(hr));

		D3D11_TEXTURE2D_DESC tempDesc;
		m_Texture->GetDesc(&tempDesc);

		m_Width = tempDesc.Width;
		m_Height = tempDesc.Height;
	}
}