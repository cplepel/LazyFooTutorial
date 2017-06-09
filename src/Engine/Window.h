//--------------------------------------------------------------------------------------------------
//
// Copyright 2017 Cody Plepel
//
// SDL2 Used under the ZLIB license.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted 
// provided that the following conditions are met :
//
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and 
// the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions 
// and the following disclaimer in the documentation and / or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
// FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
// LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//--------------------------------------------------------------------------------------------------
#pragma once

// We use FORWARD DECLARATION here to prevent having to include the h files for SDL here.
// This helps compile time but can also prevent CIRCULAR INCLUDES. We will include
// the h files in the cpp.

#include <SFML/Window.hpp>
// Window wrapper.
class Window {

public:

    //Screen dimension constants
    // TODO CPP: These need to be data driven in an inl file.
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;

    Window ();
    ~Window ();
    bool Initialize ();

    bool Terminate ();

    sf::Window& GetRawSDLWindow () { return m_window; }

    const sf::Window&  GetRawSDLWindow() const { return m_window; }

private:
    //The window we'll be rendering to
    sf::Window m_window{};

};