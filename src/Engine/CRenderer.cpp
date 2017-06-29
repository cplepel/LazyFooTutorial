#include "CRenderer.h"
#include "SFML/Graphics/Text.hpp"

//--------------------------------------------------------------------------------------------------
bool CRenderer::Initialize () {
    // Unused atm
    // If window gets more complicated initialization i will switch
    return m_window.Initialize();
}

//--------------------------------------------------------------------------------------------------
bool CRenderer::Terminate () {
    return m_window.Terminate();
}


//----------------------------------------------------------------------------------------------
// CPP TODO: Convert this to take an entity or make a pipeline
void CRenderer::Draw () {
    auto& win = m_window.GetSFMLWindow();
    win.clear();

    win.display();
}

//----------------------------------------------------------------------------------------------
void CRenderer::DrawTextImmediate (sf::Text& text) {
    auto& win = m_window.GetSFMLWindow();
    win.clear();

    win.draw(text);

    win.display();
}