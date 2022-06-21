workspace "Engine"
	architecture "x64"
	startproject "Engine"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["libs"]  = "%{prj.name}/libs"
IncludeDir["SDL2"]  = "%{prj.name}/libs/SDL2"
IncludeDir["glm"]   = "%{prj.name}/libs/glm"
IncludeDir["ImGui"] = "%{prj.name}/libs/imgui"
IncludeDir["box2D"] = "%{prj.name}/libs/box2D"
IncludeDir["lua"]   = "%{prj.name}/libs/lua"
IncludeDir["sol"]   = "%{prj.name}/libs/sol"
-- IncludeDir["ENTT"] = "%{SolutionDir}/libs/ENTT"

project "Engine"
	location "Engine"
	-- kind "ConsoleApp"
	kind "ConsoleApp"
	language "C++"
	warnings "Off"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
        	"%{prj.name}/libs/**.h",
       		"%{prj.name}/libs/**.cpp",
        	"%{prj.name}/libs/**.hpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src/includes",
		"%{prj.name}/src/includes/core",
		"%{prj.name}/src/includes/Entities",
		"%{prj.name}/src/includes/GUIPanels",
		"%{prj.name}/src/includes/Systems",
		"%{IncludeDir.libs}",
		"%{IncludeDir.SDL2}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.lua}",
        	"%{IncludeDir.sol}",
		"%{IncludeDir.box2D}"
	}

	libdirs
	{
        	"%{prj.name}/libs/SDL2",
	        "%{prj.name}/libs/imgui",
        	"%{prj.name}/libs/box2D"
	}

	links
	{
        	"SDL2",
	        "SDL2main",
        	"SDL2_image",
	        "SDL2_ttf",
        	"SDL2_mixer",
		"ImGui",
		"Box2D"
	}

	postbuildcommands
	{
		-- "{COPY} ..\\lib\\SDL2\\SDL2.dll/ ..\\bin\\" .. outputdir .. "\\Engine",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CB_PLATFORM_WINDOWS",
			"CB_BUILD_DLL"
			-- "GL_GLEXT_PROTOTYPES=1",
		}

	filter "configurations:Debug"
		defines "CB_DEBUG"
		--buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "CB_RELEASE"
		--buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "CB_DIST"
		--buildoptions "/MD"
		optimize "on"