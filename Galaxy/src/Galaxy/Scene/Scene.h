#pragma once

#include "SceneCamera.h"
#include "Galaxy/Core/Timestep.h"

namespace Galaxy
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);
	private:
		SceneCamera* camera;
	};
}