#ifndef __UI_H__
#define	__UI_H__

#include "Renderer.h"
#include "Window.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include <json/json.h>
#include <string>
#include <vector>


class UI
{
public:
	enum class LightType
	{
		P_LIGHT = 0,
		P_LIGHT_ATT = 1,
		DIR_LIGHT = 2,
		F_LIGHT = 3
	};

private:
	/*vector to store number of lights
	and their type*/
	std::vector<LightType> Lights;

	/*vector to store name of out objects
	for ui list*/
	std::vector<const char*> ObjNames;
	std::string ObjUiType;
	bool ObjisTexture = false;
	bool ObjisPath = false;
	Json::Value ObjectList;
	Window& Wnd;
	Renderer& Rnd;
	ImVec2 initRes = ImVec2(1600, 900);
	ImVec2 wndPos = ImVec2(0,0);
	Window::WindowRes wndRes;
	bool Initialize = true;
	int currSelected = 0;
	int prevSelected = 0;
	ImGuiWindowFlags flags = ( ImGuiWindowFlags_NoResize |
							   ImGuiWindowFlags_NoMove |
							   ImGuiWindowFlags_NoCollapse
							);
public:
	UI() = default;
	UI(Window& Wnd, Renderer& Rnd);
	~UI();
	void Render();
	void DrawElement();
	void AddLight(LightType type);
	void ParseJSON(Json::Value& ObjList);
	void setUI(Renderer::Shape shape);
};

#endif