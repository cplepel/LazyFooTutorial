
#include "CoreEngine.h"
#include <assert.h>

//--------------------------------------------------------------------------------------------------
bool CEngine::Initialize () {
    return m_renderer.Initialize();
}

//--------------------------------------------------------------------------------------------------
bool CEngine::Terminate() {

    bool success = m_renderer.Terminate();
    assert(success);
    return true;
}