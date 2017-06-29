//Using SDL and standard IO
#include "CoreDebug.h"
#include "CoreEngine.h"
#include "CoreUtils.h"
#include <stdio.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "CInput.h"
#include "../Encosys/EntityManager.h"
#include "RenderSystem.h"
#include "CTextureManager.h"

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

int main (int argc, char* args[]) {
    ref_(argc);
    ref_(args);


    CEngine engine;
    engine.Initialize();
    WindowsConfirmDirectory();
    
    bool success = engine.Initialize();
    if (!success) {
        printf("ENGINE FAILURE!");
        return -1;
    }

    CWindow& window = engine.GetRenderer().GetWindow();

    TEncosysManager entityManager;
    entityManager.RegisterSystem<RenderSystem>(window);

    CTextureManager textureManager;

    ECS::Entity player = entityManager.Create();
    entityManager.AddComponent<SPositionComponent>(player, 50.f, 50.f);
    entityManager.AddComponent<STextureComponent>(player, textureManager.LoadTexture("doot.png"));

    sf::Text text;
    // run the program as long as the window is open
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    while (engine.GetRenderer().WindowIsOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.PollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.Close();
            }
        }

        auto currentTime = std::chrono::high_resolution_clock::now();
        const float milliElapsed = std::chrono::duration<float, std::milli>(currentTime - lastFrameTime).count();
        entityManager.RunSystems(milliElapsed);
        lastFrameTime = currentTime;

        sf::Text toDraw;
        bool canDraw = false;
        if (CInput::IsKeyPressed(e_moveDownKey)) {
            entityManager.GetComponent<SPositionComponent>(player).m_y += milliElapsed;
            // canDraw = FormatText("Down Pressed", toDraw);
        }
        if (CInput::IsKeyPressed(e_moveRightKey)) {
            entityManager.GetComponent<SPositionComponent>(player).m_x += milliElapsed;
            // canDraw = FormatText("Right Pressed", toDraw);
        }
        if (CInput::IsKeyPressed(e_moveLeftKey)) {
            entityManager.GetComponent<SPositionComponent>(player).m_x -= milliElapsed;
            // canDraw = FormatText("Left Pressed", toDraw);
        }
        if (CInput::IsKeyPressed(e_moveUpKey)) {
            entityManager.GetComponent<SPositionComponent>(player).m_y -= milliElapsed;
            // canDraw = FormatText("Up Pressed", toDraw);
        }

        if (canDraw) {
            engine.GetRenderer().DrawTextImmediate(toDraw);
        }
    }
    engine.Terminate();

    return 0;
}