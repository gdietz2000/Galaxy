#pragma once

#include "DirectXContext.h"
#include "Galaxy/Renderer/Texture.h"

#include <wrl.h>

namespace Galaxy
{
	class DirectXTexture2D : public Texture2D
	{
	public:
		DirectXTexture2D(uint32_t width, uint32_t height);
		DirectXTexture2D(const std::string& filepath);

		virtual ~DirectXTexture2D() {}

		virtual void Bind(uint32_t index = 0) override;
		virtual void Unbind() const override;

		virtual void SetData(void* data, uint32_t size) override;
		virtual void SetDesign(TextureMode mode, glm::vec4 borderColor = glm::vec4(0.0f)) const override;

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

	private:
		DirectXContext* m_Context;

		std::string m_Path;
		uint32_t m_Width, m_Height, m_Index;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_Texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_View;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler;
	};
}