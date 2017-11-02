#include "Player.h"

GLuint Player::p1UP =    0;
GLuint Player::p1DOWN =	 0;
GLuint Player::p1RIGHT = 0;
GLuint Player::p1LEFT =  0;

GLuint Player::p2UP =    0;
GLuint Player::p2DOWN =  0;
GLuint Player::p2RIGHT = 0;
GLuint Player::p2LEFT =  0;

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
	
	if (playerNumber == 1)
	{
		p1UP =    TextureLoader::getTexture("resources/textures/p1up.png");
		p1DOWN =  TextureLoader::getTexture("resources/textures/p1down.png");
		p1RIGHT = TextureLoader::getTexture("resources/textures/p1right.png");
		p1LEFT =  TextureLoader::getTexture("resources/textures/p1left.png");
	}
	else if(playerNumber == 2){
		p2UP =    TextureLoader::getTexture("resources/textures/p2up.png");
		p2DOWN =  TextureLoader::getTexture("resources/textures/p2down.png");
		p2RIGHT = TextureLoader::getTexture("resources/textures/p2right.png");
		p2LEFT =  TextureLoader::getTexture("resources/textures/p2left.png");
	}

	sprite = new Sprite(_w, _h, _x, _y, DYNAMIC);
	sprite->setTextureMode(STATIC_TEXTURE);

	if		(playerNumber == 1) sprite->setTexture(p1DOWN);
	else if (playerNumber == 2) sprite->setTexture(p2DOWN);
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

void Player::setTexture(GLuint texture)
{
	sprite->setTexture(texture);
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
		shells[i]->draw();
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

			if      (playerNumber == 1)	this->setTexture(p1UP);
			else if (playerNumber == 2)	this->setTexture(p2UP);
		}
	}
	else if (key == KEY_S)
	{
		this->y += PLAYER_SPEED;
		if (this->direction != DOWN)
		{
			this->direction = DOWN;

			if		(playerNumber == 1) this->setTexture(p1DOWN);
			else if (playerNumber == 2) this->setTexture(p2DOWN);
		}
	}
	else if (key == KEY_D)
	{
		this->x += PLAYER_SPEED;
		if (this->direction != RIGHT)
		{
			this->direction = RIGHT;

			if		(playerNumber == 1) this->setTexture(p1RIGHT);
			else if (playerNumber == 2) this->setTexture(p2RIGHT);
		}
	}
	else if (key == KEY_A)
	{
		this->x -= PLAYER_SPEED;
		if (this->direction != LEFT)
		{
			this->direction = LEFT;

			if		(playerNumber == 1) this->setTexture(p1LEFT);
			else if (playerNumber == 2) this->setTexture(p2LEFT);
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

int& Player::getLives()
{
	return lives;
}

int& Player::getPoints()
{
	return points;
}