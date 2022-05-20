#include "WindowInst.h"

#include <iostream>

void WindowInst::WindowCloseCallBack(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		std::cout << "Message!" << std::endl;
	}
}
