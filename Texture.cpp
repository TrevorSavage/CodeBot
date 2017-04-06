#include "Texture.h"
#include <stdio.h>
#include "libraries\soil\src\SOIL.h"

Texture::Texture(const char * path) {
	textureId = SOIL_load_OGL_texture
	(
		path,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	if (0 == textureId)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}
Texture::~Texture() {}

GLuint Texture::getTextureId() {
	return textureId;
}