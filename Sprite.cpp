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
	rect->freeRes();
	glDeleteTextures(1, &texture);
}

void Sprite::freeRes()
{
	this->freeTexture();
	rect->freeRes();
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
	this->freeTexture();
	texture = TextureLoader::getTexture(pathTexture);
}

void Sprite::setTexture(GLuint _texture)
{	
	this->freeTexture();
	texture = _texture;
}

void Sprite::freeTexture()
{
	if(texture_mode != STATIC_TEXTURE) glDeleteTextures(1, &texture);
}

void Sprite::setTextureMode(TEXTURE_MODE mode)
{
	texture_mode = mode;
}

GLuint Sprite::getTexture()
{
	return texture;
}
