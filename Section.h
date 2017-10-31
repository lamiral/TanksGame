#pragma once

#include "Sprite.h"

enum SECTION_TYPE
{
	GRASS_SECTION,
	GROUND_SECTION,
	WALL_SECTION,
	WATER_SECTION,
	FLAG_SECTION
};

class Section
{
private:

	Sprite *sprite;

public:

	SECTION_TYPE type;
	float w, h, x, y;

	Section(float _w,float _h,float _x,float _y,SECTION_TYPE _type);
	~Section();

	void setTexture(const char *setTexture);
	void draw();
};