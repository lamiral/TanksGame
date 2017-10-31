#include "Player.h"

Player::Player(float _x,float _y,float _w,float _h)
{	
	w = _w;
	h = _h;
	x = _x;
	y = _y;

	direction = 1;

	sprite = new Sprite(_w, _h, _x, _y, DYNAMIC);
}

Player::~Player()
{
	delete sprite;
}

void Player::setTexture(const char *pathTexture)
{
	sprite->setTexture(pathTexture);
}

void Player::draw()
{	
	sprite->x = this->x;
	sprite->y = this->y;

	sprite->draw();
}

void Player::move(KEY_TYPE key)
{
	if (key == KEY_W)
	{
		this->y -= PLAYER_SPEED;
		if (direction != UP)
		{
			this->direction = UP;
			this->setTexture("resources/textures/up.png");
		}
	}
	else if (key == KEY_S)
	{
		this->y += PLAYER_SPEED;
		if (this->direction != DOWN)
		{
			this->direction = DOWN;
			this->setTexture("resources/textures/down.png");
		}
	}
	else if (key == KEY_D)
	{
		this->x += PLAYER_SPEED;
		if (this->direction != RIGHT)
		{
			this->direction = RIGHT;
			this->setTexture("resources/textures/right.png");
		}
	}
	else if (key == KEY_A)
	{
		this->x -= PLAYER_SPEED;
		if (this->direction != LEFT)
		{
			this->direction = LEFT;
			this->setTexture("resources/textures/left.png");
		}
	}
}