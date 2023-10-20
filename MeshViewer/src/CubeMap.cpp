#include "CubeMap.h"

#define STB_IMPLEMENTATION

CubeMap::CubeMap() : TextureID(0)
{
	VBO.SetBufferDataS(cubeMapBuf.size() * sizeof(float), cubeMapBuf.data());
	VAO.Bind();
	VBO.Bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

	VAO.UnBind();
	VBO.UnBind();
}

bool CubeMap::LoadCubeMap()
{
	bool retVal = true;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID);
	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, //target 
				0, //level
				GL_RGB, //internal format
				width,
				height, 
				0, //border
				GL_RGB, //format
				GL_UNSIGNED_BYTE, // type 
				data // pixel data type : const void *
			);
			stbi_image_free(data);
		}
		else
		{
			if(stbi_failure_reason())
				std::cout << "Cubemap texture failed to load:  " 
				<< faces[i] << ", "
				<< "Reason : "
				<< stbi_failure_reason() 
				<< std::endl;
			stbi_image_free(data);
			retVal = false;
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return retVal;
}

bool CubeMap::SetNewFaces(std::vector<std::string> newFaces)
{
	if (newFaces.size() < 6)
	{	
		std::cout << "ERROR: missing faces" << std::endl;
		return false;
	}
	faces = newFaces;

	return true;
}

void CubeMap::Draw()
{
	VAO.Bind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	VAO.UnBind();
}
