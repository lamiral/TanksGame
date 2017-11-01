#include "Sprite.h"

Sprite::Sprite(float _w,float _h,float _x,float _y,RECT_TYPE type)
{	
	w = _w;
	h = _h;
	x = _x;
	y = _y;

	rect = new Rect(_w, _h, _x, _y,WITH_TEXTURE,type);
}

Sprite::~Sprite()
{
	glDeleteTextures(1, &texture);
}

void Sprite::draw()
{	
	rect->x = this->x;
	rect->y = this->y;
	glBindTexture(GL_TEXTURE_2D, texture);
	rect->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::setTexture(const char *pathTexture)
{
	texture = TextureLoader::getTexture(pathTexture);
}

void Sprite::freeTexture()
{
	glDeleteTextures(1, &texture);
}
