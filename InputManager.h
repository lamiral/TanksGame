#pragma once

#include <GLFW\glfw3.h>

enum KEY_TYPE
{
	KEY_W = GLFW_KEY_W,
	KEY_D = GLFW_KEY_D,
	KEY_A = GLFW_KEY_A,
	KEY_S = GLFW_KEY_S,
	KEY_UP = GLFW_KEY_UP,
	KEY_DOWN = GLFW_KEY_DOWN,
	KEY_LEFT = GLFW_KEY_LEFT,
	KEY_RIGHT = GLFW_KEY_RIGHT,
	KEY_ESCAPE = GLFW_KEY_ESCAPE,
	KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT,
	KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT
};

class InputManager
{
private:
	
	GLFWwindow *window;

public:

	InputManager(GLFWwindow *_window) : window(_window) {};

	bool key_pressed(KEY_TYPE key);
};