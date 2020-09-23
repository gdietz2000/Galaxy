#pragma once

#include "Platform/Windows/DirectXContext.h"
#include "Buffer.h"
#include "wrl.h"

namespace Galaxy
{
	class Renderer3D
	{
	public:
		static void Init();
		static void DrawQuad(float color[4]);
	private:
		static DirectXContext* m_Context;

		static Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
		static Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;
		static Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;

		static Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		static Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;

		static Microsoft::WRL::ComPtr<ID3D11Buffer> m_ConstantBuffer;
		static Ref<ConstantBuffer> squareColor;
	};
}