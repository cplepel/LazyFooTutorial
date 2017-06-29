
#include "CWindow.h"
#include <assert.h>

//--------------------------------------------------------------------------------------------------
CWindow::CWindow () {
}

//--------------------------------------------------------------------------------------------------
CWindow::~CWindow () {
}

//--------------------------------------------------------------------------------------------------
bool CWindow::Initialize () {
    // TODO CPP: ContextSettings here.
    auto& videoModes = sf::VideoMode::getFullscreenModes();
    if (videoModes.empty()) {
        m_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Engine");
    }
    else {
        m_window.create(videoModes[0], "Engine");
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
bool CWindow::Terminate() {
    return true;
}
