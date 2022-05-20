#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../Object.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp"



#include <vector>

class Triangle : public Object
{
private:
	VertexArray VAO;
	VertexBuffer VBO;
	std::vector<float> TriBuf = {
	   //Vertex----------| Normal----------| Tangent---------| Bitangent-------| Texture Coordinates          
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};
	float ObjTrans[3] = {0.0f,0.0f,0.0f};
	float ObjRot[3]  = {0.0f,0.0f,0.0f};
	float ObjScale[3] = {1.0f,1.0f,1.0f};
public:
	Triangle();
	~Triangle() override;
	void Draw() override;
	void Create() override;
	float* GetData() override { return TriBuf.data(); }
	size_t  GetSize() override { return TriBuf.size() * sizeof(float); }
	float* GetTranslation() override { return ObjTrans; }
};

#endif