#ifndef RENDERER
#define RENDERER

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
#include "Model.hh"

using namespace std;

class Renderer {
public:
	Renderer();

	bool initializeRenderer();
	void deleteRenderer();

	void InitializeObjectModelVAO(GameObject* gameObject);
	void RenderObject(GameObject* gameObject);

	void TransformObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

private:
	bool loadShader(const string& shaderToLoad, GLuint& shader);

	const string SHADER_TO_LOAD = "./Assets/Shaders/basicShader";
	
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;

	GLuint vertexLoc;
	GLuint colorLoc;
	GLuint projLoc;
	GLuint viewLoc;
	GLuint TGLoc;

	// GLuint, int = VAO, modelFaces
	map<string, pair<GLuint, int>> modelVAOs;
};

#endif