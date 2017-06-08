--require "lua" -- add this to load your module

-- premake5.lua
workspace "EngineLearning"
   configurations { "Debug", "Release", "CodyTime" }
   location "../build/"

   platforms {"Native", "x86", "x64"}

   project "Render"
      kind "ConsoleApp"
      language "C++"
      targetdir "/bin/%{cfg.buildcfg}"
      location "../build/"
      includedirs {
      "../libraries/sdl/include/"
      }


      files { "render/*.h", "render/*.cpp" }

      filter "configurations:Debug"
         defines { "DEBUG" }
         symbols "On"
         links {"SDL2", "SDL2main", "SDL2test", "SDL2.dll"}

      filter "configurations:Release"
         defines { "NDEBUG" }
         optimize "On"
         links {"SDL2", "SDL2main", "SDL2test", "SDL2.dll"}

      filter "platforms:x86"
         libdirs {"../libraries/sdl/lib/x86/"}
         postbuildcommands {
         "{COPY} ../libraries/sdl/lib/x86/SDL2.dll %{cfg.targetdir}"
      }


      filter "platforms:x64"
         libdirs {"../libraries/sdl/lib/x64/"}
         postbuildcommands {
         "{COPY} ../libraries/sdl/lib/x64/SDL2.dll %{cfg.targetdir}"
      }


   project "Game"
      kind "ConsoleApp"
      language "C++"
      targetdir "../build/bin/%{cfg.buildcfg}"
      location "../build/"
      includedirs {
      "../libraries/sdl/include/"
      }

      files { "game/*.h", "game/*.cpp" }

      filter "configurations:Debug"
         defines { "DEBUG" }
         symbols "On"
         links {"SDL2", "SDL2main", "SDL2test", "SDL2.dll"}

      filter "configurations:Release"
         defines { "NDEBUG" }
         optimize "On"
         links {"SDL2", "SDL2main", "SDL2test", "SDL2.dll"}

      filter "platforms:x86"
         libdirs {"../libraries/sdl/lib/x86/"}
         postbuildcommands {
         "{COPY} ../libraries/sdl/lib/x86/SDL2.dll %{cfg.targetdir}"
      }


      filter "platforms:x64"
         libdirs {"../libraries/sdl/lib/x64/"}
         postbuildcommands {
         "{COPY} ../libraries/sdl/lib/x64/SDL2.dll %{cfg.targetdir}"
      }