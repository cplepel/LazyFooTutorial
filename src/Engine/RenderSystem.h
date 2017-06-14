#pragma once

#include "../Encosys/Entity.h"
#include "../Encosys/System.h"
#include "TextureManager.h"
#include "PositionComponent.h"
#include "TextureComponent.h"

class Window;

class RenderSystem : public ECS::CSystem {
public:
    explicit RenderSystem (Window& window) : m_window(window) {}

    virtual void PreUpdate () override;
    virtual void PostUpdate () override;

    void Update (ECS::Entity entity, const PositionComponent& position, const TextureComponent& texture);

private:
    Window& m_window;
};