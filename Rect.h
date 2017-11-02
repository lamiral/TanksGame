#pragma once

#include <GL\glew.h>

enum RECT_DRAW_TYPE{
	NON_TEXTURE,
	WITH_TEXTURE
};

enum RECT_TYPE
{
	DYNAMIC,
	STATIC
};

class Rect
{
private:

	GLuint VAO;

	float w, h;

	void init();

	RECT_DRAW_TYPE draw_type;
	RECT_TYPE      rect_type;

public:
	float x, y;

	Rect(float _w, float _h, float _x, float _y,RECT_DRAW_TYPE _type,RECT_TYPE type);
	~Rect();

	void freeRes();
	void draw();
};