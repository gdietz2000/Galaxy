#pragma once

namespace Galaxy
{
	class RendererAPI
	{
		enum class API
		{
			None = 0,
			DirectX = 1
		};

	public:
		virtual void Init() = 0;
		virtual void SetClearColor(float color[4]) = 0;
		virtual void Clear() = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}