#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__

#include "../Light.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp"
#include <string>

class PointLight : public Light
{
private:
	float linear;
	float quadratic;
	float constant;
	glm::vec3 Pos;
	glm::vec3 color;

	const std::string type = "Point";
public:
	PointLight();
	PointLight(float linear, float quadratic, float constant);
	~PointLight() {};

	std::string getType() { return type; }
	float getLinear() { return linear; }
	float getQuadratic() { return quadratic; }
	float getConstant() { return constant; }
	glm::vec3 getPosition() { return Pos; };
	glm::vec3 getLightColor() { return color; }

	float* getLinearRef() { return &linear; }
	float* getQuadraticRef() { return &quadratic; }
	float* getConstantRef() { return &constant; }
	float* getPositionRef() { return glm::value_ptr(Pos); }
	float* getLightColorRef() { return glm::value_ptr(color); }

	void setLinear(float val);
	void setQuadratic(float val);
	void setConstant(float val);
};

#endif
