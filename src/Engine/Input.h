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
//----------------------------------------------------------------------------------------------

#pragma once

#include "TypeDefs.h"
#include "InputBinding.h"

class Window;

enum EMoveKeys {
    e_moveUpKey,
    e_moveDownKey,
    e_moveRightKey,
    e_moveLeftKey
};

class Input {
public:
    static Vect2i GetMousePosition () {
        return sf::Mouse::getPosition();
    }

    static Vect2i GetMousePosition (Window& win);

    Input& GetGlobalInput () {
        static Input s_instance;
        return s_instance;
    }

    template <typename TCallback>
    void AddBinding (sf::Keyboard::Key key, const TCallback& cb, bool onPress = false) {
        m_keyboardBinds.Add(key, cb, onPress);
    }

    //----------------------------------------------------------------------------------------------
    // NOTE CPP: Maybe this is horrible.
    static bool IsKeyPressed (EMoveKeys key) {
        switch (key) {
        case e_moveRightKey:
            return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        case e_moveLeftKey:
            return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        case e_moveUpKey:
            return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        case e_moveDownKey:
            return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        default:
            return false;
        }
    }

    
private:
    KeyboardBinds  m_keyboardBinds;
};