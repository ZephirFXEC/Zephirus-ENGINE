workspace "Zephirus"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "Zephirus-Core"
	location "Zephirus-Core"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
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
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outdir .. "/Sandbox")
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

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

		targetdir ("bin/" .. outdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outdir .. "/%{prj.name}")

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