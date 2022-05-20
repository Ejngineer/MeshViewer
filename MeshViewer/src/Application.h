#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Renderer.h"
#include "UI.h"
#include "Window.h"

class Application
{
private:
	Window& Wnd;
	Renderer& Rnd;
	UI& GUI;
public:
	Application(Window& Wnd, Renderer& Rnd, UI& GUI);
	Application(Application&) = delete;
	Application& operator=(Application&) = delete;
	~Application() = default;
	int Init();
	void Run();
	void Shutdown();
};

#endif