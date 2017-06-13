
#include "CoreEngine.h"
#include <assert.h>

//--------------------------------------------------------------------------------------------------
bool Engine::Initialize () {
    return m_renderer.Initialize();
}

//--------------------------------------------------------------------------------------------------
bool Engine::Terminate() {

    bool success = m_renderer.Terminate();
    assert(success);
    return true;
}