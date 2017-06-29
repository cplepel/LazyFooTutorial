#include "RenderSystem.h"
#include "CRenderer.h"
#include <SFML/Graphics.hpp>
#include "CWindow.h"

static sf::CircleShape shape(1.f);

void RenderSystem::PreUpdate () {
    m_window.GetSFMLWindow().clear();
}

void RenderSystem::PostUpdate () {
    m_window.GetSFMLWindow().display();
}

void RenderSystem::Update (ECS::Entity, const SPositionComponent& position, const STextureComponent& texture) {
    if (const CTexture* tex = CTexture::Deref(texture.m_tag)) {
        sf::Sprite sprite;
        sprite.setTexture(tex->GetTexture());
        sprite.setPosition(position.m_x, position.m_y);
        m_window.GetSFMLWindow().draw(sprite);
    }
}