#include "Renderer.hh"

Renderer::Renderer()
{
}

bool Renderer::initializeRenderer() 
{
	return loadShader(SHADER_TO_LOAD, shaderProgram);
}

void Renderer::deleteRenderer() 
{
	glDeleteProgram(shaderProgram);
}

bool Renderer::loadShader(const string& shaderToLoad, GLuint &shader)
{
	char infoLog[512];
	GLint success;

	string tmp = "";
	string src = "";

	// Vertex shader
	ifstream in_file;
	in_file.open(shaderToLoad + ".vert");
	if (in_file.is_open()) {
		while (getline(in_file, tmp)) {
			src += tmp + '\n';
		}
	}
	else {
		cout << "ERROR: Unable to open vertex shader" << endl;
		return false;
	}
	in_file.close();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR: Unable to compile vertex shader: " << infoLog << endl;
		return false;
	}

	tmp = "";
	src = "";

	// Fragment shader
	in_file.open(shaderToLoad + ".frag");
	if (in_file.is_open()) {
		while (getline(in_file, tmp)) {
			src += tmp + '\n';
		}
	}
	else {
		cout << "ERROR: Unable to open fragment shader" << endl;
		return false;
	}
	in_file.close();

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR: Unable to compile fragment shader: " << infoLog << endl;
		return false;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR: Unable to link shader program: " << infoLog << endl;
		return false;
	}

	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}