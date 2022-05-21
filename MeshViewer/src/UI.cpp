#include "UI.h"

#include <iostream>
#include <fstream>

UI::UI(Window& Wnd, Renderer& Rnd)
	:
	Wnd(Wnd),
	Rnd(Rnd)
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(Wnd.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ParseJSON(ObjectList);
}

UI::~UI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void UI::Render()
{
	static bool opened;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	wndRes = Wnd.getResolution();
	if (initRes.x != wndRes.x || initRes.y != wndRes.y)
	{
		initRes.x = (float)wndRes.x;
		initRes.y = (float)wndRes.y;

		ImGui::SetNextWindowPos(ImVec2(initRes.x - 400,
			0));
		ImGui::SetNextWindowSize(ImVec2(400, initRes.y));

		Rnd.SetViewPort(wndRes.x - 400, wndRes.y);
		Rnd.SetupFBO(initRes.x - 400, initRes.y);
	}
	else if(Initialize)
	{
		ImGui::SetNextWindowPos(ImVec2(initRes.x - 400,
			0));
		ImGui::SetNextWindowSize(ImVec2(400, initRes.y));
		Initialize = false;
	}

	ImGui::Begin("Mesh Viewer", &opened, flags);
	ImGui::Combo("Objects", &currSelected, ObjNames.data(), (int)ObjNames.size());
	
	if (prevSelected != currSelected)
	{
		prevSelected = currSelected;
		switch (currSelected)
		{
		case 0:
			Rnd.CreateObject(Renderer::Shape::NONE);
			setUI(Renderer::Shape::NONE);
			break;
		case 1:
			Rnd.CreateObject(Renderer::Shape::TRIANGLE);
			setUI(Renderer::Shape::TRIANGLE);
			break;
		}
	}

	DrawElement();

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::AddLight(LightType type)
{
	Lights.push_back(type);
}

void UI::ParseJSON(Json::Value& ObjList)
{
	std::ifstream ifs("json/ObjectList.json");
	Json::Reader reader;
	Json::Value Obj;
	reader.parse(ifs, Obj);

	ObjList = Obj["Objects"];

	Json::FastWriter fWriter;

	for (unsigned int i = 0; i < ObjList.size(); i++)
	{
		ObjNames.push_back(ObjList[i]["name"].asCString());
	}
}

void UI::setUI(Renderer::Shape shape)
{
	ObjUiType = ObjectList[shape]["Uitype"].asString();
	ObjisTexture = ObjectList[shape]["Texture"].asBool();
}

void UI::DrawElement()
{
	if (ObjUiType == "TwoD")
	{
		ImGui::ColorEdit3("Color", Rnd.getColor());
		ImGui::Text("Transform");
		ImGui::SliderFloat2("Translation", Rnd.getTransform(), -5.0f, 5.0f);
		ImGui::SliderFloat2("Scale", Rnd.getScale(), 0.0f, 10.0f);
		ImGui::SliderFloat3("Rotation", Rnd.GetRotation(), 0.0f, 360.0f);
	}
}
