#include "TextureManager.hpp"

g2dTexture* TextureManager::loadTexture(const char* texture) {

	g2dTexture* tex = g2dTexLoad(texture, G2D_SWIZZLE);
    int w = (tex == NULL ? 10 : tex->w),
    h = (tex == NULL ? 10 : tex->h);
	

	return tex;
}