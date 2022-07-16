#include "Cube.h"

Cube::Cube()
{
	VBO.SetBufferDataS(GetSize(), GetData());
}

Cube::~Cube()
{
}

void Cube::Draw()
{
	VAO.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	VAO.UnBind();
}

void Cube::Create()
{
	VAO.Bind();
	VBO.Bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(12 * sizeof(float)));

	VAO.UnBind();
	VBO.UnBind();
}
