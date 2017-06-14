#pragma once

#include "Texture.h"

struct TextureComponent {
    explicit TextureComponent (TextureTag tag) : m_tag(tag) {}
    TextureTag m_tag{};
};