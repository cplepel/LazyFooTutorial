#include "Texture.h"

bool Texture::LoadFromFile (const char* fileName) {
    return m_texture.loadFromFile(fileName);
}