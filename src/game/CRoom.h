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

#include "GameDefines.h"
#include "TypeDefs.h"
#include "SQuad.h"

const int c_adjoiningRoomCountMax = 4;

class CRoom {
public:

    CRoom () : m_position(0.f, 0.f) {};
    ~CRoom() {};

    CRoom** GetConnectedRooms () { return m_connectedRooms; }

    CRoom* GetRoom (NGame::ERoomDirections dir) { return m_connectedRooms[(int)dir]; }

    bool HasRoom (NGame::ERoomDirections dir) { return m_connectedRooms[(int)dir] != nullptr; }

private:
    // $NOTE CPP: This is 100% not the way we should store levels. Should discuss.
    CRoom* m_connectedRooms[NGame::e_directionCount];
    Vect2f m_position{};
    Quadf  m_roomSize{};

};
