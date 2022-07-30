#ifndef __DIRECTLIGHT_H__
#define __DIRECTLIGHT_H__

#include "../Light.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp"
#include <string>

class DirectLight : public Light
{
private:
	glm::vec3 Direction = glm::vec3(0.0f);
	glm::vec3 color = glm::vec3(1.0f);

	const std::string type = "Directional";
public:
	DirectLight() {};
	DirectLight(glm::vec3 Dir) { Direction = Dir; };

	~DirectLight() {};

	glm::vec3 getDirection() { return Direction; };
	float* getDirectionRef() { return glm::value_ptr(Direction); };

	glm::vec3 getColor() { return color; };
	float* getColorRef() { return glm::value_ptr(color); };

};

#endif