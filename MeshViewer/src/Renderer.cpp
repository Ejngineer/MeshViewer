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

	shader.load(SHADERS::defaultVert, SHADERS::defaultFrag);
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
		Obj = new Triangle();
		Obj->Create();
	}
}

void Renderer::CreateShader(const std::string& path)
{
	//shader.load("../shaders/defaultvert.glsl", "../shaders/defaultfrag.glsl");
}

void Renderer::DrawObject()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		if (Obj != nullptr)
		{
			shader.Use();
			model = glm::mat4(1.0f);
			model = glm::translate(model, Trans);
			Rotate();
			model = glm::scale(model, Scale);
			shader.setMat4f("model", model);
			shader.setMat4f("view", view);
			projection = glm::perspective(glm::radians(FOV), frameWidth / frameHeight, 0.1f, 100.0f);
			//glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
			shader.setMat4f("projection", projection);
			shader.setvec3f("color", Color);
			Obj->Draw();
		}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
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
	glEnable(GL_DEPTH);
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

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Failed to create framebuffer" << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
