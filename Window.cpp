#include "Window.h"

Window::Window(int _w, int _h, const char *title)
{
	w = _w;
	h = _h;

	window = glfwCreateWindow(w,h,title,NULL,NULL);

	if (!window)
	{
		Log::error("Window did not create");
		return;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;
}

Window::~Window()
{	
	this->deleteWindow();
}

void Window::deleteWindow()
{
	if (window) {
		glfwTerminate();
		glfwDestroyWindow(window);
	}
}

bool Window::is_open()
{
	if (!window) return false;

	glfwPollEvents();
	glfwSwapBuffers(window);

	return !glfwWindowShouldClose(window);
}

GLFWwindow* Window::getWindow() const
{
	return window;
}