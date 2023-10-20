#include "VertexArray.h"

VertexArray::VertexArray() : ID(0)
{
	glGenVertexArrays(1, &ID);
	//Bind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &ID);
}

void VertexArray::Bind()
{
	glBindVertexArray(ID);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}
