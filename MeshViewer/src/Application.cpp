#include "Application.h"

#include <iostream>

Application::Application(Window& Wnd, Renderer& Rnd, UI& GUI)
	:
	Wnd(Wnd),
	Rnd(Rnd),
	GUI(GUI)
{
	Init();
};

int Application::Init()
{	
	//Rnd.SetViewPort(800, 600);
	Rnd.Enable();

	return 0;
}

void Application::Run()
{
	while (!Wnd.WindowShoudlClose())
	{
		Rnd.Clear();

		Wnd.processInput();

		GUI.Render();

		Rnd.DrawObject();

		Wnd.SwapBuffers();
	}
	
}

void Application::Shutdown()
{
	exit(0);
}
