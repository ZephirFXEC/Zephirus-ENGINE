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
IncludeDir["GLFW"] = "Zephirus-Core/vendor/GLFW/include"
IncludeDir["GLAD"] = "Zephirus-Core/vendor/GLAD/include"

include "Zephirus-Core/vendor/GLFW"
include "Zephirus-Core/vendor/GLAD"

project "Zephirus-Core"
	location "Zephirus-Core"
	kind "SharedLib"
	language "C++"

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
		"%{IncludeDir.GLAD}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"ZPH_PLATFORM_WINDOWS",
			"ZPH_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "ZPH_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "ZPH_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "ZPH_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"ZPH_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ZPH_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ZPH_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ZPH_DIST"
		optimize "On"