#include "Shell.h"

Shell::Shell(float _x, float _y, float _w, float _h, SHELL_DIRECTION _direction)
{	
	w = _w;
	h = _h;
	x = _x;
	y = _y;

	direction = _direction;
	sprite = new Sprite(w, h, x, y, DYNAMIC);
	sprite->setTexture("resources/textures/shell3.png");
}

Shell::~Shell()
{
	delete sprite;
}

void Shell::move()
{
	if		(direction == SHELL_UP)		y -= SHELL_SPEED;
	else if (direction == SHELL_DOWN)	y += SHELL_SPEED;
	else if (direction == SHELL_RIGHT)	x += SHELL_SPEED;
	else if (direction == SHELL_LEFT)	x -= SHELL_SPEED;
}

void Shell::draw()
{	
	move();

	sprite->x = this->x;
	sprite->y = this->y;

	sprite->draw();
}