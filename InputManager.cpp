#include "InputManager.h"

bool InputManager::key_pressed(KEY_TYPE key)
{
	if (glfwGetKey(window, key) == GLFW_PRESS) return true;
	else									   return false;
}