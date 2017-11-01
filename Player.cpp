#include "Player.h"

Player::Player(float _x,float _y,float _w,float _h,int _playerNumber)
{	
	w = _w;
	h = _h;
	x = _x;
	y = _y;

	lastTime = 0.0f;

	lives = 3;
	points = 0;

	playerNumber = _playerNumber;

	direction = DOWN;

	sprite = new Sprite(_w, _h, _x, _y, DYNAMIC);
}

Player::~Player()
{
	delete sprite;

	for (short i = 0; i < shells.size(); i++)
	{
		delete shells[i];
	}
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
	drawShells();
}

void Player::drawShells()
{
	for (short i = 0; i < shells.size(); i++)
	{
		if(shells[i] != nullptr) shells[i]->draw();
	}
}

void Player::move(KEY_TYPE key)
{
	if (key == KEY_W)
	{
		this->y -= PLAYER_SPEED;
		if (direction != UP)
		{
			this->direction = UP;

			sprite->freeTexture();
			if		(playerNumber == 1) this->setTexture("resources/textures/p1up.png");
			else if (playerNumber == 2) this->setTexture("resources/textures/p2up.png");
		}
	}
	else if (key == KEY_S)
	{
		this->y += PLAYER_SPEED;
		if (this->direction != DOWN)
		{
			this->direction = DOWN;

			sprite->freeTexture();
			if		(playerNumber == 1) this->setTexture("resources/textures/p1down.png");
			else if (playerNumber == 2) this->setTexture("resources/textures/p2down.png");
		}
	}
	else if (key == KEY_D)
	{
		this->x += PLAYER_SPEED;
		if (this->direction != RIGHT)
		{
			this->direction = RIGHT;

			sprite->freeTexture();
			if		(playerNumber == 1) this->setTexture("resources/textures/p1right.png");
			else if (playerNumber == 2) this->setTexture("resources/textures/p2right.png");
		}
	}
	else if (key == KEY_A)
	{
		this->x -= PLAYER_SPEED;
		if (this->direction != LEFT)
		{
			this->direction = LEFT;

			sprite->freeTexture();
			if		(playerNumber == 1) this->setTexture("resources/textures/p1left.png");
			else if (playerNumber == 2) this->setTexture("resources/textures/p2left.png");
		}
	}
}

void Player::instantiateShell(float currTime)
{	
	float deltaTime = currTime - lastTime;

	std::cout << deltaTime << std::endl;

	if (deltaTime < 1) return;

	lastTime = glfwGetTime();

	float shell_size = 10;

	if (direction == UP)
	{
		Shell *shell = new Shell(x + shell_size, y, shell_size, shell_size, SHELL_UP);
		this->shells.push_back(shell);
	}
	else if (direction == DOWN)
	{

		Shell *shell = new Shell(x + shell_size, y + w, shell_size, shell_size, SHELL_DOWN);
		this->shells.push_back(shell);
	}
	else if (direction == RIGHT)
	{
		Shell *shell = new Shell(x + w, y + (h / 2), shell_size, shell_size, SHELL_RIGHT);
		this->shells.push_back(shell);
	}
	else if (direction == LEFT)
	{
		Shell *shell = new Shell(x, y + (w / 2), shell_size, shell_size, SHELL_LEFT);
		this->shells.push_back(shell);
	}
}