#include "Section.h"

Section::Section(float _w, float _h, float _x, float _y, SECTION_TYPE _type)
{
	this->w = _w;
	this->h = _h;
	this->x = _x;
	this->y = _y;
	this->type = _type;

	sprite = new Sprite(w, h, x, y, DYNAMIC);
}

Section::~Section()
{
	delete sprite;
}

void Section::setTexture(const char *pathTexture)
{
	sprite->setTexture(pathTexture);
}

void Section::draw()
{
	sprite->x = this->x;
	sprite->y = this->y;

	sprite->draw();
}