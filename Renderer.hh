#ifndef RENDERER
#define RENDERER

#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Renderer {
public:
	Renderer();

	bool initializeRenderer();
	void deleteRenderer();

private:
	bool loadShader(const string& shaderToLoad, GLuint& shader);

	const string SHADER_TO_LOAD = "./Assets/Shaders/basicShader";
	
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
};

#endif