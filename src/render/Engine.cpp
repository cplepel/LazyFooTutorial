
#include "CoreEngine.h"
#include <assert.h>

//--------------------------------------------------------------------------------------------------
bool Engine::Initialize () {
    int res = SDL_Init(SDL_INIT_VIDEO);
    if (res < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    bool renRes = m_renderer.Initialize();
    if (renRes == false) {
        printf("SDL Windows could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
bool Engine::Terminate() {

    bool success = m_renderer.Terminate();
    assert(success);
    //Quit SDL subsystems
    SDL_Quit();
    return true;
}