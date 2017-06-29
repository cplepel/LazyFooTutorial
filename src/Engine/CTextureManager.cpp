#include "CTextureManager.h"

TTextureTag CTextureManager::LoadTexture (const char* fileName) {
    if (CTexture* texture = CTexture::Create()) {
        if (!texture->LoadFromFile(fileName)) {
            CTexture::Destroy(texture->Tag());
            return TTextureTag();
        }
        return texture->Tag();
    }
    return TTextureTag();
}