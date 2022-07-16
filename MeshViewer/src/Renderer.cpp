#include "Renderer.h"

#include <iostream>

Renderer::Renderer()
	:
	Obj(nullptr)
{
	Init();
};

void Renderer::Init()
{

	quadVAO.Bind();
	quadVBO.SetBufferDataS(frameQuad.size() * sizeof(float), frameQuad.data());

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	quadVAO.UnBind();

	//shader.load(SHADERS::defaultVert, SHADERS::defaultFrag);
	shader.load(SHADERS::phongVert, SHADERS::phongFrag);
	frameShader.load(SHADERS::frameVert, SHADERS::frameFrag);

	frameShader.Use();
	frameShader.setNum1i("frameTexture", 0);

	SetViewPort((int)frameWidth, (int)frameHeight);
	SetupFBO(frameWidth, frameHeight);
}

void Renderer::Clear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::CreateObject(const Shape& shp)
{
	if (shp == Shape::NONE)
	{
		Obj = nullptr;
	}

	if (shp == Shape::TRIANGLE)
	{
		delete Obj;
		Obj = new Triangle();
		Obj->Create();
	}

	if (shp == Shape::CUBE)
	{
		delete Obj;
		Obj = new Cube();
		Obj->Create();
	}


}

void Renderer::CreateLight(const lightType& light)
{
	if (light == lightType::NONE)
	{
		return;
	}

	if (light == lightType::P_LIGHT)
	{
		PointLight* plight = new PointLight();
		Plights.push_back(plight);
	}
}

void Renderer::CreateShader(const std::string& path)
{
	//shader.load("../shaders/defaultvert.glsl", "../shaders/defaultfrag.glsl");
}

void Renderer::setUniforms()
{
	shader.Use();
	model = glm::mat4(1.0f);
	model = glm::translate(model, Trans);
	Rotate();
	model = glm::scale(model, Scale);
	shader.setMat4f("model", model);
	shader.setMat4f("view", view);
	projection = glm::perspective(glm::radians(FOV), frameWidth / frameHeight, 1.0f, 100.0f);
	//glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	shader.setMat4f("projection", projection);
	shader.setvec3f("color", Color);

	shader.setNum1i("numPlights", int(Plights.size()));
	shader.setFloat1f("ambientStr", AmbientStrength);
	shader.setFloat1f("specStr", SpecularStrength);
	shader.setvec3f("viewPos", eye);

	for(int i = 0; i < Plights.size(); i++)
	{
		shader.setvec3f("plights[" + std::to_string(i) + "].Pos", Plights[i]->getPosition());
		shader.setvec3f("plights[" + std::to_string(i) + "].color", Plights[i]->getLightColor());
		shader.setFloat1f("plights[" + std::to_string(i) + "].linear", Plights[i]->getLinear());
		shader.setFloat1f("plights[" + std::to_string(i) + "].quadratic", Plights[i]->getQuadratic());
		shader.setFloat1f("plights[" + std::to_string(i) + "].constant", Plights[i]->getConstant());
	}
}

void Renderer::DrawObject()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (Obj != nullptr)
		{
			if (Mode == 0)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			if (Mode == 1)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			if (Mode == 2)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			}

			setUniforms();
			
			Obj->Draw();
		}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	frameShader.Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, frameTexture);
	
	quadVAO.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	quadVAO.UnBind();
}

void Renderer::SetViewPort(int width, int height)
{
	glViewport(0, 0, width, height);
}

/*Control opengl features here*/
void Renderer::Enable()
{
	glEnable(GL_DEPTH_TEST);
}

void Renderer::SetupFBO(float width, float height)
{
	frameWidth = width;
	frameHeight = height;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glGenTextures(1, &frameTexture);
	glBindTexture(GL_TEXTURE_2D, frameTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)width, (GLsizei)height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexture, 0);

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (GLsizei)width, (GLsizei)height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);

	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Failed to create framebuffer" << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::ToggleModes(int mode)
{
	Mode = mode;
}

void Renderer::Rotate()
{
	if (RotAxis.x > 0.0f)
	{
		model = glm::rotate(model, glm::radians(RotAxis.x), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (RotAxis.y > 0.0f)
	{
		model = glm::rotate(model, glm::radians(RotAxis.y), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (RotAxis.z > 0.0f)
	{
		model = glm::rotate(model, glm::radians(RotAxis.z), glm::vec3(0.0f, 0.0f, 1.0f));
	}
}
