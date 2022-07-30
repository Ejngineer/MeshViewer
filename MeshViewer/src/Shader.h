#ifndef __SHADER_H__
#define __SHADER_H__

#include "glad/glad.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp"

#include <string>

namespace SHADERS
{
	constexpr auto defaultVert = "shaders/defaultvert.glsl";
	constexpr auto defaultFrag = "shaders/defaultfrag.glsl";

	constexpr auto frameVert = "shaders/framevert.glsl";
	constexpr auto frameFrag = "shaders/framefrag.glsl";

	constexpr auto phongVert = "shaders/PhongVert.glsl";
	constexpr auto phongFrag = "shaders/PhongFrag.glsl";

	constexpr auto textureVert = "shaders/TextureVert.glsl";
	constexpr auto textureFrag = "shaders/TextureFrag.glsl";
}

class Shader
{
private:
	unsigned int ID;
public:
	Shader() : ID(NULL) {};
	~Shader() = default;
	Shader(const std::string& vertex, const std::string& fragment, const std::string& geometry = "",
		const std::string& compute = "", const std::string& Tesselation = "");
	void load(const std::string& vertex, const std::string& fragment, const std::string& geometry = "",
		const std::string& compute = "", const std::string& Tesselation = "");

	void setMat4f(const std::string& name, glm::mat4 input);
	void setNum1i(const std::string& name, int v0);
	void setvec3f(const std::string& name, glm::vec3 input);
	void setFloat1f(const std::string& name, float v0);
	void Use() { glUseProgram(ID); };


};

#endif