//Using SDL and standard IO
#include "CoreDebug.h"
#include "CoreEngine.h"
#include "CoreUtils.h"
#include <stdio.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Input.h"

#include <windows.h>
sf::Font font;

bool FormatText (const char* input, sf::Text& toSet) {

    WindowsConfirmDirectory();

    if (!font.loadFromFile("Roboto-Light.ttf")) {
        printf("ERROR LOADING FONT");
        return false;
    }

    toSet.setFont(font);
    toSet.setString(input);
    toSet.setCharacterSize(24);
    //toSet.setColor(sf::Color::Red);
    return true;
}

int main (int argc, char* args[])
{
    ref_(argc);
    ref_(args);

    Engine engine;
    engine.Initialize();
    WindowsConfirmDirectory();
    
    bool success = engine.Initialize();
    if (!success) {
        printf("ENGINE FAILURE!");
        return -1;
    }

    sf::Text text;
    // run the program as long as the window is open
    while (engine.GetRenderer().WindowIsOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        Window& window = engine.GetRenderer().GetWindow();
        while (window.PollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.Close();
            }
        }


        sf::Text toDraw;
        bool canDraw = false;
        if (Input::IsKeyPressed(e_moveDownKey)) {
            canDraw = FormatText("Down Pressed", toDraw);
        }
        else if (Input::IsKeyPressed(e_moveRightKey)) {
            canDraw = FormatText("Right Pressed", toDraw);
        }
        else if (Input::IsKeyPressed(e_moveLeftKey)) {
            canDraw = FormatText("Left Pressed", toDraw);
        }
        else if (Input::IsKeyPressed(e_moveUpKey)) {
            canDraw = FormatText("Up Pressed", toDraw);
        }

        if (canDraw) {
            engine.GetRenderer().DrawTextImmediate(toDraw);
        }
    }
    engine.Terminate();

    return 0;
}