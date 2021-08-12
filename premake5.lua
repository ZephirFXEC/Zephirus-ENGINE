workspace "Zephirus"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"]  = "Zephirus-Core/vendor/GLFW/include"
IncludeDir["GLAD"]  = "Zephirus-Core/vendor/GLAD/include"
IncludeDir["ImGui"] = "Zephirus-Core/vendor/imgui"

group "Dependencies"
	include "Zephirus-Core/vendor/GLFW"
	include "Zephirus-Core/vendor/GLAD"
	include "Zephirus-Core/vendor/imgui"

group ""

project "Zephirus-Core"
	location "Zephirus-Core"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "zphpch.h"
	pchsource "Zephirus-Core/src/zphpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"


		defines 
		{
			"ZPH_PLATFORM_WINDOWS",
			"ZPH_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "ZPH_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "ZPH_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "ZPH_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Zephirus-Core/vendor/spdlog/include",
		"Zephirus-Core/src"
	}

	links 
	{
		"Zephirus-Core"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines 
		{
			"ZPH_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ZPH_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "ZPH_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "ZPH_DIST"
		runtime "Release"
		optimize "On"