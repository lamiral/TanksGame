#pragma once

#include <GL\glew.h>
#include <SOIL.h>
#include "Log.h"

class TextureLoader
{
public:

	static GLuint getTexture(const char *filepath);
};