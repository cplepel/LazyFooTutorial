
#include "CoreEngine.h"
#include <assert.h>

//--------------------------------------------------------------------------------------------------
bool Engine::Initialize () {
    return true;
}

//--------------------------------------------------------------------------------------------------
bool Engine::Terminate() {

    bool success = m_renderer.Terminate();
    assert(success);
    return true;
}