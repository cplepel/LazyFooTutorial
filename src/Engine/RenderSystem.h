#pragma once

#include "../Encosys/System.h"
#include "CTextureManager.h"
#include "CoreEngine.h"

class CWindow;

class RenderSystem : public ECS::System {
public:
    explicit RenderSystem (CWindow& window) : m_window(window) {}

    virtual void PreUpdate () override;
    virtual void PostUpdate () override;

    void Update (ECS::Entity entity, const SPositionComponent& position, const STextureComponent& texture);

private:
    CWindow& m_window;
};