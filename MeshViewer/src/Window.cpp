#include "Window.h"

#include <iostream>


Window::Window(const std::string&title) : wndTitle(title)
{
	initWindow();
}

Window::~Window()
{
	/*Destroy window*/
	glfwDestroyWindow(window);
	glfwTerminate();
}

int Window::initWindow()
{
	/*Initialize GLFW and check to see if it succeeded*/
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	/*Needed for obtaining video mode*/
	monitor = glfwGetPrimaryMonitor();

	mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	
	/*Create Application window*/
	window = glfwCreateWindow(1600, 900, wndTitle.c_str(), NULL, NULL);
	
	if (!window)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
	}
	
	/*make the context of our window current*/
	glfwMakeContextCurrent(window);

	glfwSetWindowUserPointer(window, wndInst);

	auto func = [](GLFWwindow* w)
	{
		static_cast<WindowInst*>(glfwGetWindowUserPointer(w))->WindowCloseCallBack(w);
	};

	glfwSetWindowCloseCallback(window, func);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad" << std::endl;

	}

	return 0;
}

void Window::SetTitle(const std::string& title)
{
	wndTitle = title;
	glfwSetWindowTitle(window, title.c_str());
}

bool Window::WindowShoudlClose()
{
	return glfwWindowShouldClose(window);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

Window::WindowRes Window::getResolution()
{
	Window::WindowRes wndRes;
	glfwGetFramebufferSize(window, &wndRes.x, &wndRes.y);

	return wndRes;
}



