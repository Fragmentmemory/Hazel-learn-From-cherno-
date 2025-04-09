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
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Wzpch.h"
	pchsource "Wizar/src/Wzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
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
		cppdialect "C++17"
		systemversion "latest"
		buildoptions { "/utf-8" }
		
		defines
		{
			"WZ_PLATFORM_WINDOWS",
			"WZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "WZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "WZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "WZ_DIST"
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
		cppdialect "C++17"
		systemversion "latest"
		buildoptions { "/utf-8" }

		defines
		{
			"WZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "WZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "WZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "WZ_DIST"
		runtime "Release"
		optimize "On"