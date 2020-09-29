#pragma once
#include "gxpch.h"

#include "Core.h"
#include "Timestep.h"
#include "Galaxy/Events/Event.h"

#include "Galaxy/Renderer/Framebuffer.h"

namespace Galaxy
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width, Height;

		WindowProps(const std::string& title = "Galaxy Engine",
			uint32_t width = 1280, uint32_t height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate(Timestep ts) = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual void* GetContext() const = 0;

		virtual Ref<Framebuffer> GetFramebuffer() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());

		operator bool() { return this != nullptr; }
	};
}