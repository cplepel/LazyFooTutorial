
#include "Window.h"
#include <assert.h>
#include <SDL.h>

//--------------------------------------------------------------------------------------------------
Window::Window () {
}

//--------------------------------------------------------------------------------------------------
Window::~Window () {
    assert(m_window == nullptr);
}

//--------------------------------------------------------------------------------------------------
bool Window::Initialize () {
    m_window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    assert(m_window != nullptr);

    // Init screen surface.
    m_activeSurface = SDL_GetWindowSurface(m_window);
    assert(m_activeSurface != nullptr);
    return m_activeSurface != nullptr && m_window != nullptr;
}

//--------------------------------------------------------------------------------------------------
bool Window::Terminate() {
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
    return true;
}
