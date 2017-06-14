--require "lua" -- add this to load your module

-- premake5.lua
workspace "EngineLearning"
    configurations { "Debug", "Release" }
    location "../build/"

    platforms {"Native", "x86", "x64", "Windows", "Mac"}
    
    warnings "Extra"
    flags {"FatalWarnings"}
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
            "../libraries/sfml/include/",
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
            ["Encosys"] = {"Encosys/*"}
        }

        filter "configurations:Debug"
            defines { "SFML_STATIC","DEBUG" }
            symbols "On"
            links {"sfml-graphics-s-d", "sfml-system-s-d", "sfml-window-s-d", "sfml-network-s-d", "sfml-audio-s-d",  "glew32",  "winmm", "gdi32", "freetype", "jpeg", "openal32", "ws2_32", "opengl32", "glu32"}
            debugdir "../build/bin/Debug"

        filter "configurations:Release"
            defines { "SFML_STATIC", "NDEBUG", "RELEASE" }
            optimize "On"
            links {"sfml-graphics-s", "sfml-system-s", "sfml-window-s", "sfml-network-s", "sfml-audio-s",  "glew32",  "winmm", "gdi32", "freetype", "jpeg", "openal32", "ws2_32", "opengl32", "glu32"}
            debugdir "../build/bin/Release"

        filter "platforms:x86"
            libdirs {"../libraries/sfml/lib/x86/lib/", "../libraries/glew/lib/x86/"}

        filter "platforms:x64"
            libdirs {"../libraries/sfml/lib/x64/lib/", "../libraries/glew/lib/x64"}


    project "Game"
        kind "ConsoleApp"
        language "C++"
        targetdir "../build/bin/%{cfg.buildcfg}"
        location "../build/"
        includedirs {
            "../libraries/sfml/include/"
        }

        files { "game/*.h", "game/*.cpp" }

        filter "configurations:Debug"
            defines { "SFML_STATIC", "DEBUG" }
            symbols "On"
            links {"sfml-graphics-s-d", "sfml-system-s-d", "sfml-window-s-d", "sfml-network-s-d", "sfml-audio-s-d", "glew32",  "winmm", "gdi32", "freetype", "jpeg", "openal32", "ws2_32", "opengl32", "glu32"}

        filter "configurations:Release"
            defines {"SFML_STATIC" , "NDEBUG", "RELEASE",}
            optimize "On"
            links {"sfml-graphics-s", "sfml-system-s", "sfml-window-s", "sfml-network-s", "sfml-audio-s",  "glew32", "winmm", "gdi32", "freetype", "jpeg", "openal32", "ws2_32", "opengl32", "glu32"}

        filter "platforms:x86"
            libdirs {"../libraries/sfml/lib/x86/lib/", "../libraries/glew/lib/x86/"}


        filter "platforms:x64"
            libdirs {"../libraries/sdl/lib/x64/lib/", "../libraries/glew/lib/x64/"}
