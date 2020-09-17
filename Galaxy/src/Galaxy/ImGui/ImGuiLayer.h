#pragma once

#include "Galaxy/Core/Layer.h"

#include "Galaxy/Events/ApplicationEvent.h"
#include "Galaxy/Events/KeyEvent.h"
#include "Galaxy/Events/MouseEvent.h"

#ifndef DirectXIncluded
#include "d3d11.h"
#pragma comment (lib, "d3d11.lib")
#include <DirectXMath.h>
#define DirectXIncluded
#endif

namespace Galaxy
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event&) override;

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void Begin();
		void End();
	private:
		bool m_BlockEvents = true;
	};
}