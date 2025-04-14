#ifndef RENDERER_HH
#define RENDERER_HH

#include <iostream>
#include <fstream>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameObject.hh"

using namespace std;

class Renderer {
public:
	Renderer();

	bool InitializeRenderer();
	void DeleteRenderer();

	void InitializeObjectModelVAO(GameObject* gameObject);
	void InitializeObjectModelTexture(GameObject* gameObject);
	void RenderObject(GameObject* gameObject);

	void TransformObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	void ClearRenderer();

	void CameraViewMatrix(const glm::mat4 VM, const glm::mat4 PM);

private:
	bool LoadShader(const string& shaderToLoad, GLuint& shader);

	const string SHADER_TO_LOAD = "./Assets/Shaders/basicShader";
	
	GLuint LoadTextureFromFile(const string& filename, int textureType);

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;

	GLuint vertexLoc;
	GLuint colorLoc;
	GLuint uvLoc;
	GLuint projLoc;
	GLuint viewLoc;
	GLuint TGLoc;
	GLuint bendLoc;
	GLuint textureLoc;

	// GLuint, int = VAO, modelFaces
	map<string, pair<GLuint, int>> modelVAOs;
	map<string, GLuint> textureLocators;
};

#endif