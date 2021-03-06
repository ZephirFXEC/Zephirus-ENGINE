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
IncludeDir["GLM"] = "Zephirus-Core/vendor/GLM"
IncludeDir["stb_image"] = "Zephirus-Core/vendor/stb_image"


group "Dependencies"
	include "Zephirus-Core/vendor/GLFW"
	include "Zephirus-Core/vendor/GLAD"
	include "Zephirus-Core/vendor/imgui"

group ""

project "Zephirus-Core"
	location "Zephirus-Core"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "zphpch.h"
	pchsource "Zephirus-Core/src/zphpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/GLM/**.hpp",
		"%{prj.name}/vendor/GLM/**.inl"
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.stb_image}"
		
		
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
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
	cppdialect "C++17"
	staticruntime "on"

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
		"Zephirus-Core/src",
		"Zephirus-Core/vendor",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.ImGui}"
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