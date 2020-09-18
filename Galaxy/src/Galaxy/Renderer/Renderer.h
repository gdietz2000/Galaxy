#pragma once
#include "Galaxy/Core/Application.h"
namespace Galaxy 
{
	class Renderer
	{
	public:
		static void Init();
		static void SetClearColor(float color[4]);
		static void Clear();
	};
}