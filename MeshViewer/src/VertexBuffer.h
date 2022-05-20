#ifndef __VERTEXBUFFER_H__
#define __VERTEXBUFFER_H__

#include "glad/glad.h"

class VertexBuffer
{
private:
	unsigned int ID;
public:
	VertexBuffer();
	VertexBuffer(size_t size, void* data);
	~VertexBuffer();
	void Bind();
	void UnBind();
	void SetBufferDataS(size_t size, void* data);
};


#endif