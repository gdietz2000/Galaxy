#pragma once

namespace Galaxy {

	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() {};

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		virtual void* Get() = 0;
	};
}