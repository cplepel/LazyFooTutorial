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

#include <sfml/System/Vector2.hpp>
#include <sfml/System/Vector3.hpp>
#include "CoreError.h"

namespace Math {

    template <typename T>
    T Dot (const sf::Vector2<T>& l, const sf::Vector2<T>& r) {
        return l.x * r.x + l.y * r.y;
    }

    template <typename T>
    T Dot (const sf::Vector3<T>& l, const sf::Vector3<T>& r) {
        return l.x * r.x + l.y * r.y + l.z * r.z;
    }

    // Here is a reasonable explanation, though not total.
    // http://allenchou.net/2013/07/cross-product-of-2d-vectors/
    // Essentially, the sign of the result of this will tell you whether the 
    // second vector (r) is on the left or right side of the first vector.
    template <typename T>
    T Cross (const sf::Vector2<T>& l, const sf::Vector2<T>& r) {
        return l.x * r.y - r.x * l.y;
    }

    //----------------------------------------------------------------------------------------------
    // Returns orthogonal vector in 2d
    template <typename T>
    sf::Vector2<T> Cross (const sf::Vector2<T>& in) {
        return sf::Vector2<T>(in.y, -in.x);
    }

    //----------------------------------------------------------------------------------------------
    // Returns the length of the vector.
    template <typename T>
    T Magnitude (const sf::Vector2<T>& in) {
        ASSERT_IS_NOT_INTEGRAL(T);
        return sqrtf(SquaredMagnitude(in));
    }

    //----------------------------------------------------------------------------------------------
    template <typename T>
    T SquaredMagnitude (const sf::Vector2<T>& in) {
        return Dot(in, in)
    }

    //----------------------------------------------------------------------------------------------
    // Normalize
    template <typename T>
    void MakeUnitVector (sf::Vector2<T>& in) {
        T mag = Magnitude(in);
        in.x / mag;
        in.y / mag;
    }

    //----------------------------------------------------------------------------------------------
    template <typename T>
    sf::Vector2<T> MakeUnitVector (const sf::Vector2<T>& in) {
        T mag = Magnitude(in);
        return sf::Vector2<T>(in.x / mag, in.y / mag);
    }

    //----------------------------------------------------------------------------------------------
    // Returns the length of the vector.
    template <typename T>
    T Magnitude (const sf::Vector3<T>& in) {
        ASSERT_IS_NOT_INTEGRAL(T);
        return sqrtf(SquaredMagnitude(in));
    }

    //----------------------------------------------------------------------------------------------
    template <typename T>
    T SquaredMagnitude (const sf::Vector3<T>& in) {
        return Dot(in, in)
    }

    //----------------------------------------------------------------------------------------------
    template <typename T>
    void MakeUnitVector (sf::Vector3<T>& in) {
        T mag = Magnitude(in);
        in.x / mag;
        in.y / mag;
        in.z / mag;
    }

    //----------------------------------------------------------------------------------------------
    template <typename T>
    sf::Vector3<T> MakeUnitVector (const sf::Vector3<T>& in) {
        T mag = Magnitude(in);
        return sf::Vector3<T>(in.x / mag, in.y / mag, in.z / mag);
    }

    //----------------------------------------------------------------------------------------------
    template <typename T>
    bool IsOnRightOf (const sf::Vector2<T>& forwardVec, const sf::Vector2<T>& origin, const sf::Vector2<T>& point) {
        return IsOnRightOf(forwardVec, point - origin);
    }

    //----------------------------------------------------------------------------------------------
    template <typename T>
    bool IsOnRightOf (const sf::Vector2<T>& forwardVec, const sf::Vector2<T>& other) {
        return Cross(forwardVec, other) < 0;
    }

    //----------------------------------------------------------------------------------------------
    template <typename T>
    T AngleBetween (const sf::Vector2<T>& l, const sf::Vector2<T>& r) {
        ASSERT_IS_NOT_INTEGRAL(T);
        T magL = Magnitude(l);
        T magR = Magnitude(r);
        return acosf(Dot(l, r) / (magL * magR));
    }
}