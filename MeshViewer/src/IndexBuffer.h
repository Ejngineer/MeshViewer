#ifndef __INDEXBUFFER_H__
#define __INDEXBUFFER_H__

#include "glad/glad.h"

class IndexBuffer
{
private:
	unsigned int ID;
public:
	IndexBuffer();
	IndexBuffer(size_t size, void* data);
	~IndexBuffer();
	void Bind();
	void UnBind();
	void SetBufferDataS(size_t size, void* data);
};


#endif
