#include "CTexture.h"

bool CTexture::LoadFromFile (const char* fileName) {
    return m_texture.loadFromFile(fileName);
}