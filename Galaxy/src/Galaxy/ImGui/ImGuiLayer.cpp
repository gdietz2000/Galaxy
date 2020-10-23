#include "gxpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_dx11.h"

#include "Galaxy/Core/Application.h"
#include "Platform/Windows/DirectXContext.h"

namespace Galaxy
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{
		ImGui_ImplDX11_InvalidateDeviceObjects();
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();

		OnDetach();
	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", 18.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", 18.0f);

		//ImGui::StyleColorsDark();
		//SetLightColorTheme();
		SetDarkColorTheme();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplDX11_CreateDeviceObjects();
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender(Timestep ts)
	{

	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.m_Handled |= e.IsInCategory(CategoryMouse) & io.WantCaptureMouse;
			e.m_Handled |= e.IsInCategory(CategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		//Rendering
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

	void ImGuiLayer::SetLightColorTheme()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_WindowBg] = ImVec4{ 0.9f, 0.905f, 0.91f, 1.0f };
		style.Colors[ImGuiCol_ChildBg] = ImVec4{ 0.9f, 0.905f, 0.91f, 1.0f };
		style.Colors[ImGuiCol_PopupBg] = ImVec4{ 0.9f, 0.905f, 0.91f, 1.0f };
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.9f, 0.905f, 0.91f, 1.0f };

		//Headers
		style.Colors[ImGuiCol_Header] = ImVec4{ 0.8f, 0.805f, 0.81f, 1.0f };
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.7f, 0.705f, 0.71f, 1.0f };
		style.Colors[ImGuiCol_HeaderActive] = ImVec4{ 0.85f, 0.8505f, 0.851f, 1.0f };

		//Buttons
		style.Colors[ImGuiCol_Button] = ImVec4{ 0.8f, 0.805f, 0.81f, 1.0f };
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.7f, 0.705f, 0.71f, 1.0f };
		style.Colors[ImGuiCol_ButtonActive] = ImVec4{ 0.85f, 0.8505f, 0.851f, 1.0f };

		//Frame BG
		style.Colors[ImGuiCol_FrameBg] = ImVec4{ 0.8f, 0.805f, 0.81f, 1.0f };
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.7f, 0.705f, 0.71f, 1.0f };
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.85f, 0.8505f, 0.851f, 1.0f };

		//Tabs
		style.Colors[ImGuiCol_Tab] = ImVec4{ 0.85f, 0.8505f, 0.851f, 1.0f };
		style.Colors[ImGuiCol_TabHovered] = ImVec4{ 0.78f, 0.7805f, 0.781f, 1.0f };
		style.Colors[ImGuiCol_TabActive] = ImVec4{ 0.88f, 0.8805f, 0.881f, 1.0f };
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.85f, 0.8505f, 0.851f, 1.0f };
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.8f, 0.805f, 0.81f, 1.0f };

		//Titles
		style.Colors[ImGuiCol_TitleBg] = ImVec4{ 0.85f, 0.8505f, 0.851f, 1.0f };
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.85f, 0.8505f, 0.851f, 1.0f };
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.85f, 0.8505f, 0.851f, 1.0f };

		style.Colors[ImGuiCol_Text] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}

	void ImGuiLayer::SetDarkColorTheme()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		//Headers
		style.Colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		style.Colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		//Buttons
		style.Colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		style.Colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		//Frame BG
		style.Colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		//Tabs
		style.Colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		style.Colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		style.Colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		//Titles
		style.Colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}
}