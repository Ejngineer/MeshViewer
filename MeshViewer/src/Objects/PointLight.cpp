#include "PointLight.h"

PointLight::PointLight()
{
	linear = 0.7f;
	quadratic = 1.8f;
	constant = 1.0f;
	Pos = glm::vec3(0.0f);
	color = glm::vec3(1.0f);
}

PointLight::PointLight(float linear, float quadratic, float constant)
	:
	linear(linear),
	quadratic(quadratic),
	constant(constant)
{
}

void PointLight::setLinear(float val)
{
	linear = val;
}

void PointLight::setQuadratic(float val)
{
	quadratic = val;
}

void PointLight::setConstant(float val)
{
	constant = val;
}


