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

#include <sfml/System/Vector2.hpp>
#include <sfml/System/Vector3.hpp>
// Note CPP: These type defs are just so we don't have the sf:: namespace everywhere in engine code.
// More typedefs can be added. 

// Including math ones here so we dont include Math.h everywhere
using Vect2i = sf::Vector2<int>;
using Vect2f = sf::Vector2<float>;
using Vect2u = sf::Vector2<unsigned int>;
using Vect3i = sf::Vector3<int>;
using Vect3f = sf::Vector3<float>;
using Vect3u = sf::Vector3<unsigned int>;