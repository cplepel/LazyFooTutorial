#include "RenderSystem.h"
#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include "Window.h"

static sf::CircleShape shape(1.f);

void RenderSystem::PreUpdate () {
    m_window.GetSFMLWindow().clear();
}

void RenderSystem::PostUpdate () {
    m_window.GetSFMLWindow().display();
}

void RenderSystem::Update (ECS::Entity, const PositionComponent& position, const TextureComponent& texture) {
    if (const Texture* tex = Texture::Deref(texture.m_tag)) {
        sf::Sprite sprite;
        sprite.setTexture(tex->GetTexture());
        sprite.setPosition(position.m_x, position.m_y);
        m_window.GetSFMLWindow().draw(sprite);
    }
}