#ifndef __RENDERER_H__
#define	__RENDERER_H__

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include  "Object.h"
#include "Objects/Triangle.h"
#include "Objects/Cube.h"
#include "Objects/Model.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Light.h"
#include "Objects/PointLight.h"
#include "Objects/DirectLight.h"
#include "CubeMap.h"



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
		TRIANGLE,
		CUBE,
		MODEL
	};

	enum class lightType
	{
		NONE,
		P_LIGHT,
		DIR_LIGHT
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
	void CreateObject(const Shape& shp, const char* path = nullptr);

	/**/
	void CreateLight(const lightType& light);

	/*Remove light from light list*/
	void DeletePLight();

	void DeleteDLight();

	/*Bind shader to our renderer*/
	void CreateShader(const std::string& path);

	/*Function to setup uniform data passed to shaders*/
	void setUniforms();

	/*Function to setup uniform data passed to shaders for skybox*/
	//void setSkyBoxUniforms();

	/*Invoke draw call for our object*/
	void DrawObject();

	/*Invoke draw call for our skybox*/
	void DrawCubeMap();

	/*Functions for drawing everytihng in our scene (Object, skybox, etc)*/
	void DrawScene();

	/*Retrieve tranform data from our Obj data member*/
	//float* GetObjectTranslation() { return Obj->GetTranslation(); }

	/*Set viewport values*/
	void SetViewPort(int width, int height);

	/*Enable all opengl settings*/
	void Enable();

	/*Setup Framebuffer to render texture to*/
	void SetupFBO(float width, float height);

	/*Toggle render mode*/
	void ToggleModes(int mode = 0);

	/*Toggle shader mode*/
	void ToggleShader(int mode = 0);

	/*Return fov*/
	float* getFOV() { return &FOV; }

	/*Change shader color uniform value*/
	float* getColor() { return glm::value_ptr(Color); }

	/*Change object coordinates*/
	float* getTransform()  { return glm::value_ptr(Trans); }

	/*Change object scale*/
	float* getScale() { return glm::value_ptr(Scale); }

	float* GetRotation() { return glm::value_ptr(RotAxis); }
	
	/*Change object rotation*/
	void Rotate();

	/*Retrive pointer to specific point light position*/
	float* getPlightPos(int idx) { return Plights[idx]->getPositionRef(); }

	float* getPlightColor(int idx) { return Plights[idx]->getLightColorRef(); }

	float* getPlightConstant(int idx) { return Plights[idx]->getConstantRef(); }

	float* getPlightLinear(int idx) { return Plights[idx]->getLinearRef(); }

	float* getPlightQuadratic(int idx) { return Plights[idx]->getQuadraticRef(); }

	float* getDLightDirection(int idx) { return DLights[idx]->getDirectionRef(); }

	float* getDLightColor(int idx) { return DLights[idx]->getColorRef(); }

	float* getAmbient() { return &AmbientStrength; }

	float* getSpecular() { return &SpecularStrength; }

	size_t getNumPointLights() { return Plights.size(); }

	size_t getNumDirLights() { return DLights.size(); }

	float GetFrameWidth() { return frameWidth; }
	float GetFrameHeight() { return frameHeight; }
	glm::mat4 GetViewMatrix() { return view; }
	
private:
	/*framebuffer texture is applied to this quad*/
	std::vector<float> frameQuad = 
	{
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	};

	/*light data members*/
	std::vector<PointLight*> Plights;
	std::vector<DirectLight*> DLights;

private:
	/*data members*/
	VertexArray quadVAO;
	VertexBuffer quadVBO;
	unsigned int FBO;
	unsigned int RBO;
	unsigned int frameTexture;
	Shader frameShader;

	/*fixed camera vectors*/
	const glm::vec3 eye = glm::vec3(0.0f, 0.0f, 3.0f);
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 center = glm::vec3(0.0f);

	/*MVP matrices*/
	glm::mat4 model = glm::mat4(1.0f);
	const glm::mat4 view = glm::lookAt(eye, center, up);
	glm::mat4 projection = glm::mat4(0.0f);

	/*Projection requires "Field of view" value.
	can be adjusted*/
	float FOV = 45.0f;

	/*Initial frameBuffer resolution*/
	float frameWidth = 1200.0f;
	float frameHeight = 900.0f;
	
	/*geometry/model data members*/
	Object* Obj;

	/*shader uniforms*/
	Shader shader;
	Shader SkyBoxShader;
	glm::vec3 Color = glm::vec3(1.0f);
	glm::vec3 Trans = glm::vec3(0.0f);
	glm::vec3 Scale = glm::vec3(1.0f);
	glm::vec3 RotAxis = glm::vec3(0.0f);
	float AmbientStrength = 0.5f;
	float SpecularStrength = 2.0f;

	/*Variables to change how object is drawn*/
	int RenderMode = 0;
	int ShaderMode = 0;

	CubeMap SkyBox;

};

#endif
