#ifndef __OBJECT_H__
#define	__OBJECT_H__

#include "Shader.h"

class Object
{
public:
	Object() {};
	virtual ~Object() = default;
	virtual void Draw() = 0;
	virtual void Create() = 0;
	virtual float* GetData() = 0;
	virtual size_t GetSize() = 0;
	virtual void setPath(const char* path) = 0;
	virtual void setShader(Shader& shader) = 0;
	//virtual float* GetTranslation() = 0;
};


#endif
