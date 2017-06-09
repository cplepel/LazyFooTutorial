//Using SDL and standard IO
#include "CoreEngine.h"
#include <stdio.h>
#include "ResourceManager.h"


int main (int argc, char* args[])
{
    Engine engine;
    
    bool success = engine.Initialize();
    if (!success) {
        printf("ENGINE FAILURE!");
        return -1;
    }

    Renderer& render = engine.GetRenderer();
    Window& window = render.GetWindow();

    SDL_Window* sdlWin = window.GetRawSDLWindow();
    SDL_Surface* sdlSurf = window.GetRawSDLWindowSurface();

    // TODO CODY: Discuss with team asset loading.
    ResourceManager rem; 
    SDL_Surface* newSurf = nullptr;
    rem.LoadDemoMedia(newSurf);
    window.BlitNewSurface(newSurf);

    // We were successful, let's get the screen adn window and render.
    //Fill the surface white
    SDL_FillRect(sdlSurf, NULL, SDL_MapRGB(sdlSurf->format, 0xFF, 0xFF, 0xFF));

    //Update the surface
    SDL_UpdateWindowSurface(sdlWin);

    //Wait two seconds
    SDL_Delay(2000);
       
    engine.Terminate();

    return 0;
}