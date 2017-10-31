#pragma once

#include <GL/glew.h>
#include <GLFW\glfw3.h>

#include "Log.h"

class Window
{
private:

	GLFWwindow *window;
	int w, h;

public:
	
	Window(int w, int h, const char *title);
	~Window();

	void deleteWindow();

	bool is_open();

	GLFWwindow* getWindow() const;
};