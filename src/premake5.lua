--require "lua" -- add this to load your module

-- premake5.lua
workspace "EngineLearning"
    configurations { "Debug", "Release" }
    location "../build/"

    platforms {"Native", "x86", "x64", "Windows", "Mac"}
    
    warnings "Extra"
    flags {"FatalWarnings", "MultiProcessorCompile"}
    postbuildcommands {
        "{COPY} ../data/images/**.* %{cfg.targetdir}",
        "{COPY} ../data/fonts/**.* %{cfg.targetdir}"
    }
    project "Engine"
        kind "ConsoleApp"
        language "C++"
        targetdir "../build/bin/%{cfg.buildcfg}"
        location "../build/"
        includedirs {
            "../libraries/SDL/include/",
            "../libraries/glew/include/"
        }

        files { "engine/*.h", "engine/*.cpp", "Encosys/*.h", "Encosys/*.cpp" }

        vpaths {
            ["Engine"] = {"engine/*Engine*.h", "engine/*Engine*.cpp"} ,
            ["Debug"] = {"engine/*Debug*.h", "engine/*Debug*.cpp"} ,
            ["CoreUtils"] = {"engine/*Utils*.h", "engine/*Util*.cpp"} ,
            ["Input"] = {"engine/*Input*.h", "engine/InputBinding.h"} ,
            ["Math"] = {"engine/*Vect*.*", "engine/*Math*.*"},
            ["Render"] = {"engine/*Window*.*", "engine/*Render*.*"},
            ["Encosys"] = {"Encosys/*"},
            ["Camera"] = {"Engine/CCamera*.*"}
        }

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
            links {  "SDL2", "SDL2Main", "SDL2Test"}
            debugdir "../build/bin/Debug"
			-- defines "SFML_STATIC",
			-- "sfml-graphics-s-d", "sfml-system-s-d", "sfml-window-s-d", "sfml-network-s-d", "sfml-audio-s-d", "freetype","glew32",  "winmm", "gdi32", "jpeg", "openal32", "ws2_32", "opengl32", "glu32",

        filter "configurations:Release"
            defines {  "NDEBUG", "RELEASE" }
            optimize "On"
            links {  "SDL2", "SDL2Main", "SDL2Test"}
            debugdir "../build/bin/Release"
			-- "SFML_STATIC",
			-- "sfml-graphics-s", "sfml-system-s", "sfml-window-s", "sfml-network-s", "sfml-audio-s","freetype", "glew32",  "winmm", "gdi32", "jpeg", "openal32", "ws2_32", "opengl32", "glu32",
        filter "platforms:x86"
            libdirs { "../libraries/glew/lib/x86/", "../libraries/SDL/lib/x86/"}
			-- "../libraries/sfml/lib/x86/lib/",
        filter "platforms:x64"
            libdirs { "../libraries/glew/lib/x64", "../libraries/SDL/lib/x64/"}
			-- "../libraries/sfml/lib/x64/lib/",

    project "Game"
        kind "ConsoleApp"
        language "C++"
        targetdir "../build/bin/%{cfg.buildcfg}"
        location "../build/"
        includedirs {
            "../libraries/SDL/include/",
            "Engine/",
            "EncoSys"
        }

        files { "game/*.h", "game/*.cpp" }

        vpaths {
            ["World"] = {"game/CWorld*.*", "game/CRoom*.*", "game/CLevel*.*"} ,
            ["GameCore"] = {"game/Game*.*"} 
        }

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
            links { "SDL2", "SDL2main", "SDL2test"}
			-- "sfml-graphics-s-d", "sfml-system-s-d", "sfml-window-s-d", "sfml-network-s-d", "sfml-audio-s-d","freetype","glew32",  "winmm", "gdi32",  "jpeg", "openal32", "ws2_32", "opengl32", "glu32", 
        filter "configurations:Release"
            defines { "NDEBUG", "RELEASE",}
            optimize "On"
            links {  "SDL2", "SDL2main", "SDL2test"}
			-- "sfml-graphics-s", "sfml-system-s", "sfml-window-s", "sfml-network-s", "sfml-audio-s","freetype","glew32", "winmm", "gdi32",  "jpeg", "openal32", "ws2_32", "opengl32", "glu32",
        filter "platforms:x86"
            libdirs {"../libraries/sfml/lib/x86/lib/", "../libraries/glew/lib/x86/"}


        filter "platforms:x64"
            libdirs {"../libraries/sdl/lib/x64/lib/", "../libraries/glew/lib/x64/", "../libraries/SDL/lib/x64/"}
