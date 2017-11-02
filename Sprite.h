#pragma once

#include "TextureLoader.h"
#include "Rect.h"

enum TEXTURE_MODE
{
	STATIC_TEXTURE, //ALL GAME
	DYNAMIC_TEXTURE //FREE TEXTURE
};

class Sprite
{
private:

	GLuint texture;
	Rect *rect;
	TEXTURE_MODE texture_mode;

public:

	float w, h, x, y;

	Sprite(float _w,float _h,float x,float y,RECT_TYPE type);
	~Sprite();

	void draw();

	void freeTexture();

	void setTexture(const char *filepath);
	void setTexture(GLuint _texture);
	void setTextureMode(TEXTURE_MODE mode);
	void freeRes();

	GLuint getTexture();
};