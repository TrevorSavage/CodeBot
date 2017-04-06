#pragma once
#include "libraries\glew\glew.h"
#include "libraries\soil\src\SOIL.h"

class Texture {
public:
	Texture(const char * path);
	~Texture();

	GLuint getTextureId();

private:
	GLuint textureId;


};