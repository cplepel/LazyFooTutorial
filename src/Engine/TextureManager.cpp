#include "TextureManager.h"

TextureTag TextureManager::LoadTexture (const char* fileName) {
    if (Texture* texture = Texture::Create()) {
        if (!texture->LoadFromFile(fileName)) {
            Texture::Destroy(texture->Tag());
            return TextureTag();
        }
        return texture->Tag();
    }
    return TextureTag();
}