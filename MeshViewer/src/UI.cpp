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
	static int selected = 0;
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
	ImGui::Combo("Objects", &selected, ObjNames.data(), (int)ObjNames.size());
	
	switch (selected)
	{
	case 0:
		Rnd.CreateObject(Renderer::Shape::NONE);
		break;
	case 1:
		Rnd.CreateObject(Renderer::Shape::TRIANGLE);
		AddElement(UIType::TwoD);
		break;
	
	}

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::AddElement(const UIType& type)
{
	UIelements.push_back(type);
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

void UI::CreateElement(const UIType& type) const
{
	if (type == UIType::TwoD)
	{
		//ImGui::Begin("2D Object");
		//ImGui::ColorEdit4("Color", );
		//ImGui::Text("Transform");
		//ImGui::SliderFloat3("Translation", Rnd.GetObjectTranslation(), 0.0f, 1.0f);
	}
}
