#pragma once

#include <iostream>
#include <vector>
#include "Sprite.h"
#include "InputManager.h"
#include "Shell.h"
#include "TextureLoader.h"

enum DIRECTION
{
	UP = 0,
	DOWN = 1,
	RIGHT = 2,
	LEFT = 3
};

#define PLAYER_SPEED 5

class Player
{
private:
	
	static GLuint p1UP;
	static GLuint p1DOWN;
	static GLuint p1RIGHT;
	static GLuint p1LEFT;

	static GLuint p2UP;
	static GLuint p2DOWN;
	static GLuint p2RIGHT;
	static GLuint p2LEFT;

	Sprite *sprite;

	float lastTime;

	int lives;
	int points;
	int playerNumber;
	
public:
	
	std::vector<Shell*> shells;

	DIRECTION direction;
	float x,y,w,h;

	Player(float _x,float _y,float _w,float _h,int _playerNumber);
	~Player();

	void setTexture(const char *pathTexture);
	void setTexture(GLuint texture);

	void draw();

	void drawShells();
	void instantiateShell(float currTime);

	void move(KEY_TYPE key);

	int& getLives();
	int& getPoints();
};