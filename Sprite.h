#pragma once

#include "TextureLoader.h"
#include "Rect.h"

class Sprite
{
private:

	GLuint texture;
	Rect *rect;

public:

	float w, h, x, y;

	Sprite(float _w,float _h,float x,float y,RECT_TYPE type);
	~Sprite();

	void draw();

	void freeTexture();
	void setTexture(const char *filepath);
};