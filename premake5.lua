workspace "Wizar"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Wizar/vendor/GLFW/include"
IncludeDir["Glad"] = "Wizar/vendor/Glad/include"
IncludeDir["ImGui"] = "Wizar/vendor/imgui"
IncludeDir["glm"] = "Wizar/vendor/glm"

include "Wizar/vendor/GLFW"
include "Wizar/vendor/Glad"
include "Wizar/vendor/imgui"

project "Wizar"
	location "Wizar"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "wzpch.h"
	pchsource "Wizar/src/wzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		" _CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"WZ_PLATFORM_WINDOWS",
			"WZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines {"WZ_DEBUG","WZ_ENABLE_ASSERTS"}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "WZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "WZ_DIST"
		runtime "Release"
		optimize "on"

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
		"Wizar/vendor/spdlog/include",
		"Wizar/src",
		"Wizar/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Wizar"
	}

	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"WZ_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines {"WZ_DEBUG","WZ_ENABLE_ASSERTS"}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "WZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "WZ_DIST"
		runtime "Release"
		optimize "on"