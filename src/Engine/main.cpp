//Using SDL 
#include <SDL.h>
#include <stdio.h>

#define ref_(x) x
//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};




// Let's declare width and height.
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// GLOBALS
// Gonna render to this window
SDL_Window* gWindow = nullptr;

// The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

SDL_Surface* gCurrentSurface = nullptr;

SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];





// DONT WORRY ABOUT REFACTORING ATM, JUST WORRY ABOUT FUN
// Starts up SDL and creates the window
bool Init ();

// Loads media
bool LoadMedia ();

// Frees media and shuts down SDL
void Close ();

bool Init () {
    // Initialize SDL
    bool initialized = SDL_Init(SDL_INIT_VIDEO) >= 0;
    if (initialized) {
        // Let's get a window goin
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow) {
            // Get the window's surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
        else {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            initialized = false;
        }
    }
    else {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    return initialized;
}

SDL_Surface* LoadSurface (std::string path) {
    // Load image at path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
    }
    return loadedSurface;
}

bool LoadMedia () {
    //Loading success flag
    bool success = true;

    //Load default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = LoadSurface("press.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        printf("Failed to load default image!\n");
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = LoadSurface("up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        printf("Failed to load up image!\n");
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = LoadSurface("down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        printf("Failed to load down image!\n");
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = LoadSurface("left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        printf("Failed to load left image!\n");
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = LoadSurface("right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        printf("Failed to load right image!\n");
        success = false;
    }

    return success;
}

void FreeSurface (SDL_Surface* surface) {
    SDL_FreeSurface(surface);
    surface = nullptr;
}

void Close () {
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
        FreeSurface(gKeyPressSurfaces[i]);
    }

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    // Quit SDL Subsystems
    SDL_Quit();
}


int main (int argc, char* args[]) {
    ref_(argc);
    ref_(args);

    if (Init()) {
        if (LoadMedia()) {

            bool quit = false;

            // This is a poll event for key, mouse, that stuff.
            SDL_Event e;

            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    // User requests to quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                // Apply the image.
                SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

                // must update.

                SDL_UpdateWindowSurface(gWindow);

                SDL_Delay(2000);
            }
            printf("Quit was hit?");
        }
        else {
            printf("Failed to load media!\n");
        }
    }
    else {
        printf("Failed to initialize!\n");
    }

    Close();


    return 0;
}