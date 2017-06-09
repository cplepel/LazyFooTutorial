#include "Renderer.h"

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