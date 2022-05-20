#ifndef __WINDOW_H__
#define	__WINDOW_H__

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "WindowInst.h"
#include <string>

class Window
{	
private:
	static float constexpr initWidth = 1200.0f;
	static float constexpr initHeight = 900.0f;
	std::string wndTitle;
	GLFWwindow* window = nullptr;
	const GLFWvidmode* mode = nullptr;
	GLFWmonitor* monitor = nullptr;
	WindowInst* wndInst;
public:
	struct WindowRes
	{
		int x = static_cast<int>(initWidth);
		int y = static_cast<int>(initHeight);
	};
public:
	Window() = default;
	Window(const std::string&title);
	~Window();
	Window& operator=(Window&) = delete;
	int initWindow();
	void SetTitle(const std::string& title);
	bool WindowShoudlClose();
	
	void SwapBuffers();
	void processInput();
	GLFWwindow* GetWindow() { return window; }
	WindowRes getResolution();
};

#endif
