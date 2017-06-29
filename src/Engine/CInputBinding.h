//--------------------------------------------------------------------------------------------------
//
// Copyright 2017 Cody Plepel, Cat Morgan, Matthew Grubb, Geoff Tucker
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

#include <functional>
#include <type_traits>
#include <vector>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

// Inspired by dabbertorres
template <typename T>
class CInputBinding {
    // This leverages some "simple" template-fu to detect if the template type
    // we have for this binding is the same as Mouse button. If it is, use their release type
    // if it is not, use the keyboards. This will not work for joysticks yet.
    static constexpr sf::Event::EventType EventRelease = std::is_same<T, sf::Mouse::Button>::value ? sf::Event::MouseButtonReleased : sf::Event::KeyReleased;
    static constexpr sf::Event::EventType EventPress = std::is_same<T, sf::Mouse::Button>::value ? sf::Event::MouseButtonPressed : sf::Event::KeyPressed;

public:
    // std::function is a class that represents a function, and it takes as its
    // template argument a signature. In this case void Func(const sf::Time& t);
    using TCallback = std::is_function<void(const sf::Time&)>;

    explicit CInputBinding (T in, const TCallback& c, bool p = false) 
        : m_input(in), m_callback(c), m_onPress(p) {

    }

    // By Copy is ok here
    T GetInput () const {
        return m_input;
    }

    //----------------------------------------------------------------------------------------------
    // TryExecuteCallback will attempt to call the keybinding.
    bool TryExecuteCallback (const sf::Event& ev) const {
        bool released = ev.type == EventRelease;
        bool pressed = ev.type == EventPress;
        bool myInput = (std::is_same<T, sf::Mouse::Button>::value) ? ev.mouseButton.button : ev.key.code;
        
        // Do we need to respond?
        if (!pressed && !released || !myInput) {
            return false;
        }

        sf::Time elapsed = sf::Time::Zero;

        if (m_onPress) {
            if (released) {
                return false;
            }
        }
        else {
            elapsed = m_clock.restart();
            if (pressed) {
                return false;
            }
        }

        m_callback(elapsed);

        return true;
    }

private:

    T m_input;
    TCallback m_callback;
    // if true, means if key is pressed, if false means if key is released
    bool m_onPress;
    // Keeps track of the time the key has been/was held for
    mutable sf::Clock m_clock;
};

template <typename T>
class BindingManager {
public:
    using BindingType = CInputBinding<T>;

    void Add (T input, const typename BindingType::TCallback& f, bool onPress = false) {
        m_bindings.emplace_back(input, f, onPress);
    }

    void CheckAndRunBindings (const sf::Event& e) {
        for (auto&& keyBind : m_bindings) {
            keyBind.TryExecuteCallback(e);
        }
    }

private:
    std::vector<BindingType> m_bindings;
};

using KeyboardBinds = BindingManager<sf::Keyboard::Key>;