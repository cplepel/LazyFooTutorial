# EngineLearning
A simple SDL 2D Tile Engine.

In order to build, you need to download a few pieces of software.

First, we need premake5 and its exe to be placed in the src directory. Link: https://premake.github.io/download.html

Second, you need the SFML library directory placed in libraries/SFML/. The folder structure should be sfml/lib/x64/lib or lib/x86/lib. Download  2.4.2 (the version we support) here https://www.sfml-dev.org/download/sfml/2.4.2/

For ease of development, I have included a .zip of the libraries directory that you can just extract and the game should run.

Finally, open a command prompt in the src directory and enter premake5 vs2015 to build a 2015 solution for windows. Check premake documentation for other build types.