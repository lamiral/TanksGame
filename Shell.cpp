#include "Shell.h"

GLuint Shell::shell_texture = 0;

Shell::Shell(float _x, float _y, float _w, float _h, SHELL_DIRECTION _direction)
{	
	w = _w;
	h = _h;
	x = _x;
	y = _y;

	shell_texture = TextureLoader::getTexture("resources/textures/shell3.png");

	direction = _direction;
	sprite = new Sprite(w, h, x, y, DYNAMIC);
	sprite->setTexture(shell_texture);
	sprite->setTextureMode(STATIC_TEXTURE);
}

Shell::~Shell()
{	
	sprite->freeRes();
	delete sprite;
}

void Shell::move()
{	
	if		(this->direction == SHELL_UP)		y -= SHELL_SPEED;
	else if (this->direction == SHELL_DOWN)		y += SHELL_SPEED;
	else if (this->direction == SHELL_RIGHT)	x += SHELL_SPEED;
	else if (this->direction == SHELL_LEFT)		x -= SHELL_SPEED;
}

void Shell::draw()
{	
	move();

	sprite->x = this->x;
	sprite->y = this->y;

	sprite->draw();
}