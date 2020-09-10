workspace "Galaxy"
	architecture "x64"
	 startproject "Sandbox"

	 configurations 
	 {
		"Debug",
		"Release"
	 }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	project "Galaxy"
		location "Galaxy"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "On"

		pchheader "gxpch.h"
		pchsource "Galaxy/src/gxpch.cpp"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include"
		}

		defines 
		{
			"_CRT_SECURE_NO_WARNINGS"
		}

		filter "system:windows"
			systemversion "latest"

			defines
			{
				"GX_PLATFORM_WINDOWS"
			}

			filter "configurations:Debug"
				defines "GX_DEBUG"
				runtime "Debug"
				symbols "On"

			filter "configurations:Release"
				defines "GX_RELEASE"
				runtime "Release"
				optimize "On"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "On"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin/" .. outputdir .. "/%{prj.name}")

		files 
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Galaxy/src",
			"Galaxy/vendor/spdlog/include",
			"Galaxy/vendor"
		}

		links
		{
			"Galaxy"
		}

		filter "system:windows"
			systemversion "latest"

			defines 
			{
				"GX_PLATFORM_WINDOWS"
			}

			filter "configurations:Debug"
				defines "GX_DEBUG"
				runtime "Debug"
				symbols "On"

			filter "configurations:Release"
				defines "GX_RELEASE"
				runtime "Release"
				optimize "On"