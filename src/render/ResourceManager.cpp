#include "ResourceManager.h"
#include "CoreEngine.h"

//--------------------------------------------------------------------------------------------------
bool ResourceManager::LoadDemoMedia (SDL_Surface* surf) {
    // TEST IMAGE
    // Load splash image
    surf = SDL_LoadBMP("hello_world.bmp");
    if (surf == nullptr) {
        printf("Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError());
        return false;
    }

    return true;
}

