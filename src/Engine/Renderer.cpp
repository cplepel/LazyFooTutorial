#include "Renderer.h"
#include "SFML/Graphics/Text.hpp"

//--------------------------------------------------------------------------------------------------
bool Renderer::Initialize () {
    // Unused atm
    // If window gets more complicated initialization i will switch
    return m_window.Initialize();
}

//--------------------------------------------------------------------------------------------------
bool Renderer::Terminate () {
    return m_window.Terminate();
}


//----------------------------------------------------------------------------------------------
// CPP TODO: Convert this to take an entity or make a pipeline
void Renderer::Draw () {
    auto& win = m_window.GetSFMLWindow();
    win.clear();

    win.display();
}

//----------------------------------------------------------------------------------------------
void Renderer::DrawTextImmediate (sf::Text& text) {
    auto& win = m_window.GetSFMLWindow();
    win.clear();

    win.draw(text);

    win.display();
}