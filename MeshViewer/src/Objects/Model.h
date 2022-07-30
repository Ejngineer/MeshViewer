#ifndef __MODEL_H__
#define __MODEL_H__

#include "../stb_image/stb_image.h"
#include "../Shader.h"
#include "Mesh.h"
#include "../Object.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <iostream>

class Model : public Object
{
private:
	std::vector<Mesh> meshes;
	std::string directory;
	const char* path;
	std::vector<Texture> textures_loaded;

	float ObjTrans[3] = { 0.0f,0.0f,0.0f };
	float ObjRot[3] = { 0.0f,0.0f,0.0f };
	float ObjScale[3] = { 1.0f,1.0f,1.0f };

	Shader* shader;

	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName);

	unsigned int CreateTexture(const char* path, std::string directory);

public:
	Model()
	{
		shader = nullptr;
	}

	void Create() override;
	void Draw() override;

	void setPath(const char* path) {
		this->path = path;
	}
	void setShader(Shader& shader) {
		this->shader = &shader;
	};

	float* GetData() override { return nullptr; }
	size_t  GetSize() override { return 0; }
};


#endif