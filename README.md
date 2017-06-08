# EngineLearning
A simple SDL 2D Tile Engine.

In order to build, you need to download two pieces of software.

First, we need premake5 and its exe to be placed in the src directory. Link: https://premake.github.io/download.html

Second, you need the SDL library directory placed in libraries/sdl/. The lib folder should be copied here as is. Download only the Development Library here: https://www.libsdl.org/download-2.0.php

Finally, open a command prompt in the src directory and enter premake5 vs2015 to build a 2015 solution for windows. Check premake documentation for other build types.