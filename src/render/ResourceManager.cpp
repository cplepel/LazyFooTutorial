#include "ResourceManager.h"
#include "CoreEngine.h"

//--------------------------------------------------------------------------------------------------
bool ResourceManager::LoadDemoMedia (SDL_Surface* surf) {
    // TEST IMAGE
    std::string imagePath = BuildMediaPath("hello_world.bmp");
    
    // Load splash image
    surf = SDL_LoadBMP(imagePath.c_str());
    if (surf == nullptr) {
        printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
        return false;
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
// Must be a better way to load assets
std::string ResourceManager::BuildMediaPath (const char* str) {
    if (str == nullptr) {
        return false;
    }

    static const char* resPath = "../../../data/images/";

    return std::string(resPath) + str;
}