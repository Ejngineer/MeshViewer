#ifndef __RENDERER_H__
#define	__RENDERER_H__

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include  "Object.h"
#include "Objects/Triangle.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

/*Singleton for creation and deletion of 
geomety/models and shaders. Also responsible for
invoking draw calls*/
class Renderer
{
public:
	/*enumerate the types of geometry
	that can be drawn*/
	enum Shape
	{
		NONE,
		TRIANGLE
	};
public:
	/*Constructors/destructor*/
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer& operator=(Renderer&&) = delete;
	~Renderer() = default;

	/*Member functions*/
	void Init();

	/*Clear bits and set background color for the frame*/
	void Clear();

	/*Bind geometry to our renderer*/
	void CreateObject(const Shape& shp);

	/*Bind shader to our renderer*/
	void CreateShader(const std::string& path);

	/*Invoke draw call for our object*/
	void DrawObject();

	/*Retrieve tranform data from our Obj data member*/
	float* GetObjectTranslation() { return Obj->GetTranslation(); }

	/*Set viewport values*/
	void SetViewPort(int width, int height);

	/*Enable all opengl settings*/
	void Enable();

	/*Setup Framebuffer to render texture to*/
	void SetupFBO(float width, float height);

private:
	/*framebuffer texture is applie to this quad*/
	std::vector<float> frameQuad = 
	{
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	};

private:
	/*data members*/
	VertexArray quadVAO;
	VertexBuffer quadVBO;
	unsigned int FBO;
	unsigned int frameTexture;
	Shader frameShader;

	/*fixed camera vectors*/
	static glm::vec3 constexpr eye = glm::vec3(0.0f, 0.0f, 3.0f);
	static glm::vec3 constexpr up = glm::vec3(0.0f, 1.0f, 0.0f);
	static glm::vec3 constexpr center = glm::vec3(0.0f);

	/*MVP matrices*/
	glm::mat4 model = glm::mat4(1.0f);
	const glm::mat4 view = glm::lookAt(eye, center, up);
	glm::mat4 projection = glm::mat4(0.0f);

	/*Projection requires "Field of view" value
	can be adjusted*/
	float FOV = 45.0f;

	/*Initial frameBuffer resolution*/
	float frameWidth = 1200.0f;
	float frameHeight = 900.0f;
	
	/*geometr/model data members*/
	Object* Obj;
	Shader shader;
};

#endif
