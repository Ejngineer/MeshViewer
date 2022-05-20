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
	enum class UIType
	{
		TwoD=0,
		ThreeD=1,
		OBJ=2,
		TEXTURE=3,
		P_LIGHT=4,
		DIR_LIGHT=5
	};

private:
	std::vector<UIType> UIelements;
	std::vector<const char*> ObjNames;
	Json::Value ObjectList;
	Window& Wnd;
	Renderer& Rnd;
	ImVec2 initRes = ImVec2(1600, 900);
	ImVec2 wndPos = ImVec2(0,0);
	Window::WindowRes wndRes;
	bool Initialize = true;
	ImGuiWindowFlags flags = ( ImGuiWindowFlags_NoResize |
							   ImGuiWindowFlags_NoMove |
							   ImGuiWindowFlags_NoCollapse
							);
public:
	UI() = default;
	UI(Window& Wnd, Renderer& Rnd);
	~UI();
	void Render();
	void CreateElement(const UIType& type) const;
	void AddElement(const UIType& type);
	void ParseJSON(Json::Value& ObjList);
};

#endif