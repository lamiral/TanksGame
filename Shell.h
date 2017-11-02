#pragma once

#include "Sprite.h"
#include "TextureLoader.h"

#define SHELL_SPEED 10

enum SHELL_DIRECTION
{
	SHELL_UP,
	SHELL_DOWN,
	SHELL_RIGHT,
	SHELL_LEFT
};

class Shell
{
private:
	
	static GLuint shell_texture;
	Sprite *sprite;
	void move();

public:

	SHELL_DIRECTION direction;

	float x, y, w, h;

	Shell(float x,float y,float w,float h,SHELL_DIRECTION direction);
	~Shell();

	void draw();
};
