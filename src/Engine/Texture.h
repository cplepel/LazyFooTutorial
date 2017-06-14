#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "TagAllocator.h"

static constexpr size_t g_texturePoolSize = 1024;

class Texture : public TagRecycler<Texture, g_texturePoolSize> {
public:
    using TagType = TagRecycler<Texture, g_texturePoolSize>::TagType;

    bool LoadFromFile (const char* fileName);

    sf::Texture& GetTexture () { return m_texture; }
    const sf::Texture& GetTexture () const { return m_texture; }

private:
    sf::Texture m_texture{};
};
using TextureTag = Texture::TagType;
