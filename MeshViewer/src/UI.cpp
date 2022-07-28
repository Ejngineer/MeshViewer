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
	if(Initialize)
	{
		ImGui::SetNextWindowPos(ImVec2(initRes.x - 400,
			0));
		ImGui::SetNextWindowSize(ImVec2(400, initRes.y));
		Initialize = false;
	}
	else if (initRes.x != wndRes.x || initRes.y != wndRes.y)
	{
		initRes.x = (float)wndRes.x;
		initRes.y = (float)wndRes.y;

		ImGui::SetNextWindowPos(ImVec2(initRes.x - 400,0));
		ImGui::SetNextWindowSize(ImVec2(400, initRes.y));

		Rnd.SetViewPort(wndRes.x - 400, wndRes.y);
		Rnd.SetupFBO(initRes.x - 400, initRes.y);
	}

	ImGui::Begin("Mesh Viewer", &opened, flags);
	ImGui::Combo("Objects", &currSelected, ObjNames.data(), (int)ObjNames.size());
	
	if (prevSelected != currSelected)
	{
		prevSelected = currSelected;
		switch (currSelected)
		{
		case 0:
			setUI(currSelected);
			Rnd.CreateObject(Renderer::Shape::NONE);
			break;
		case 1:
			setUI(currSelected);
			Rnd.CreateObject(Renderer::Shape::TRIANGLE);
			break;
		case 2:
			setUI(currSelected);
			Rnd.CreateObject(Renderer::Shape::CUBE);
			break;
		case 3:
			path = ObjectList[currSelected]["Path"].asString();
			setUI(currSelected);
			Rnd.CreateObject(Renderer::Shape::MODEL, path.c_str());
			break;
		}
	}
	DrawElement();

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

void UI::setUI(int selected)
{
	ObjUiType = ObjectList[selected]["Uitype"].asString();
	ObjisTexture = ObjectList[selected]["Texture"].asBool();
}

void UI::DrawElement()
{
	if (ObjUiType != "NONE")
	{
		if (ImGui::Button("Render Shader"))
		{
			Rnd.ToggleModes(0);
		}
		ImGui::SameLine();
		if (ImGui::Button("Render Lines"))
		{
			Rnd.ToggleModes(1);
		}
		ImGui::SameLine();
		if (ImGui::Button("Render Points"))
		{
			Rnd.ToggleModes(2);
		}

		
	}

	if (ObjUiType == "TwoD")
	{
		ImGui::ColorEdit3("Color", Rnd.getColor());
		ImGui::Text("Transform");
		ImGui::SliderFloat2("Translation", Rnd.getTransform(), -5.0f, 5.0f);
		ImGui::SliderFloat2("Scale", Rnd.getScale(), 0.0f, 10.0f);
		ImGui::SliderFloat3("Rotation", Rnd.GetRotation(), 0.0f, 360.0f);
		ImGui::SliderFloat("Ambient Strength", Rnd.getAmbient(), 0.0f, 1.0f);
		ImGui::SliderFloat("Specular Strenth", Rnd.getSpecular(), 2.0f, 1024.0f);
	}

	if (ObjUiType == "ThreeD")
	{
		ImGui::ColorEdit3("Color", Rnd.getColor());
		ImGui::Text("Transform");
		ImGui::SliderFloat2("Translation", Rnd.getTransform(), -5.0f, 5.0f);
		ImGui::SliderFloat3("Scale", Rnd.getScale(), 0.0f, 10.0f);
		ImGui::SliderFloat3("Rotation", Rnd.GetRotation(), 0.0f, 360.0f);
		ImGui::SliderFloat("Ambient Strength", Rnd.getAmbient(), 0.0f, 1.0f);
		ImGui::SliderFloat("Specular Strenth", Rnd.getSpecular(), 0.0f, 4096.0f);
	}

	if (ObjUiType == "Model")
	{
		ImGui::ColorEdit3("Color", Rnd.getColor());
		ImGui::Text("Transform");
		ImGui::SliderFloat2("Translation", Rnd.getTransform(), -5.0f, 5.0f);
		ImGui::SliderFloat3("Scale", Rnd.getScale(), 0.0f, 10.0f);
		ImGui::SliderFloat3("Rotation", Rnd.GetRotation(), 0.0f, 360.0f);
		ImGui::SliderFloat("Ambient Strength", Rnd.getAmbient(), 0.0f, 1.0f);
		ImGui::SliderFloat("Specular Strenth", Rnd.getSpecular(), 0.0f, 4096.0f);
	}

	ImGui::Text("Lights");
	if (ImGui::Button("Add PointLight"))
	{
		Rnd.CreateLight(Renderer::lightType::P_LIGHT);
	}

	for (int i = 0; i < Rnd.getNumPointLights(); i++)
	{
		std::string name = "Point Light " + std::to_string(i + 1);
		std::string position = "Position##" + std::to_string(i + 1);
		std::string linear = "Linear##" + std::to_string(i + 1);
		std::string quadratic = "Quadratic##" + std::to_string(i + 1);
		std::string constant = "Constant##" + std::to_string(i + 1);
		std::string color = "Light Color##" + std::to_string(i + 1);

		ImGui::Text(name.c_str());
		ImGui::SliderFloat3(position.c_str(), Rnd.getPlightPos(i), -5.0f, 5.0f);
		ImGui::SliderFloat(linear.c_str(), Rnd.getPlightLinear(i), 0.0f, 5.0f);
		ImGui::SliderFloat(quadratic.c_str(), Rnd.getPlightQuadratic(i), 0.0f, 5.0f);
		ImGui::SliderFloat(constant.c_str(), Rnd.getPlightConstant(i), 0.0f, 5.0f);
		ImGui::ColorEdit3(color.c_str(), Rnd.getPlightColor(i));
	}
}
