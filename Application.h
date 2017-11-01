#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <Windows.h>
#include <iostream>

#include "Player.h"
#include "Math.h"
#include "Log.h"
#include "Window.h"
#include "Shader.h"
#include "Sprite.h"
#include "Map.h"
#include "MapLoader.h"
#include "InputManager.h"
#include "Collision.h"

#define MAP_SIZE 30
#define PLAYER_SPEED 5

class Application
{
private:

	int w, h;

	Player *player1;
	Player *player2;

	Map *map;

	InputManager *inputManager;
	Window *window;
	Shader *shader;

	glm::mat4 Ortho;

	void clear();
	void initAppObjects();
	void initOrtho();
	void key();
	void collision();
	void restartGame();
	void checkGame();

	bool initGL();

public:

	Application(const char *title);
	~Application();

	void start();
};