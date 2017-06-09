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
#include <string>

struct SDL_Surface;

class ResourceManager {
public:

    // TODO: Temporary function to test loading surfaces.
    // SDL_Surface is a software rendered target, we need textures.
    bool LoadDemoMedia (SDL_Surface* surf);
private:

};