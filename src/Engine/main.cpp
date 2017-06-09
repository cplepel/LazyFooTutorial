//Using SDL and standard IO
#include "CoreEngine.h"
#include "CoreUtils.h"
#include <stdio.h>
#include <SFML/Window.hpp>

int main (int argc, char* args[])
{
    ref_(argc);
    ref_(args);

    Engine engine;
    
    bool success = engine.Initialize();
    if (!success) {
        printf("ENGINE FAILURE!");
        return -1;
    }


    sf::Window window(sf::VideoMode(800, 600), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    engine.Terminate();

    return 0;
}