#include "Application.h"
#include <iostream>

int main()
{
	/*Initialize components*/
	Window Wnd("Mesh Viewer");
	Renderer Rnd;
	UI GUI(Wnd, Rnd);
	/*APP INIT*/
	Application* App = new Application(Wnd, Rnd, GUI);
	/*APP RUN*/
	App->Run();
	/*APP SHUTDOWN*/
	App->Shutdown();
	return 0;
}