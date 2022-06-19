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
IncludeDir["libs"]  = "libs"
IncludeDir["SDL2"]  = "libs/SDL2"
IncludeDir["glm"]   = "libs/glm"
IncludeDir["ImGui"] = "libs/imgui"
IncludeDir["box2D"] = "libs/box2D"
IncludeDir["lua"]   = "libs/lua"
IncludeDir["sol"]   = "libs/sol"
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
		"src/**.h",
		"src/**.cpp",
        	"libs/**.h",
       		"libs/**.cpp",
        	"libs/**.hpp",
		-- "libs/SDL2/**.h",
		-- "libs/glm/**.hpp",
		-- "libs/glm/**.inl",
		-- "libs/box2D/**.h",
        	-- "libs/imgui/**.h",
		-- "libs/imgui/**.cpp",
        	-- "libs/lua/**.h",
        	-- "libs/lua/**.hpp",
        	-- "libs/sol/**.hpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"src/includes",
		"src/includes/core",
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
        	"libs/SDL2",
	        "libs/imgui",
        	"libs/box2D"
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