#ifndef __CUBEMAP_H__
#define __CUBEMAP_H__

#include "glad/glad.h"
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include "stb_image/stb_image.h"
#include "Objects/Cube.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

class CubeMap
{
private:
	std::vector<float> cubeMapBuf = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	std::vector<std::string> faces = {
		"skyboxes\\clearsky\\right.jpg",
		"skyboxes\\clearsky\\left.jpg",
		"skyboxes\\clearsky\\top.jpg",
		"skyboxes\\clearsky\\bottom.jpg",
		"skyboxes\\clearsky\\front.jpg",
		"skyboxes\\clearsky\\back.jpg"
	};
public:
	CubeMap();
	~CubeMap() = default;
	bool LoadCubeMap();
	bool SetNewFaces(std::vector<std::string> newFaces);
	unsigned int GetTextureID() { return TextureID; }
	void Draw();
private:
	unsigned int TextureID;
	VertexArray VAO;
	VertexBuffer VBO;
	

};

#endif
