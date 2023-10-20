#include "VertexBuffer.h"

#include <iostream>

VertexBuffer::VertexBuffer() : ID(0)
{
	glGenBuffers(1, & ID);
	//glBindBuffer(GL_ARRAY_BUFFER, ID);
}

VertexBuffer::VertexBuffer(size_t size, void* data) : ID(0)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &ID);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetBufferDataS(size_t size, void* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
