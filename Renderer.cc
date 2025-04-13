#include "Renderer.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Renderer::Renderer()
{
}

bool Renderer::InitializeRenderer() 
{
	bool lS = LoadShader(SHADER_TO_LOAD, shaderProgram);

	glUseProgram(shaderProgram);

	projLoc = glGetUniformLocation(shaderProgram, "PM");
	viewLoc = glGetUniformLocation(shaderProgram, "VM");
	uvLoc = glGetUniformLocation(shaderProgram, "uv");
	vertexLoc = glGetAttribLocation(shaderProgram, "vertex");
	colorLoc = glGetAttribLocation(shaderProgram, "color");
	TGLoc = glGetUniformLocation(shaderProgram, "TG");
	textureLoc = glGetUniformLocation(shaderProgram, "textureSampler");
	glUniform1i(textureLoc, 0);

	LoadTextureFromFile("./Assets/Textures/Texture_Tower.jpg");

	return lS;
}

void Renderer::InitializeObjectModelVAO(GameObject* gameObject) 
{
	string modelName = gameObject->ModelName();
	if (modelVAOs.find(modelName) != modelVAOs.end()) return;

	Model model;
	model.load(modelName);

	glGenVertexArrays(1, &modelVAOs[modelName].first);
	glBindVertexArray(modelVAOs[modelName].first);
	modelVAOs[modelName].second = model.faces().size();

	GLuint VBOs[3];
	glGenBuffers(3, VBOs);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.faces().size() * 3 * 3, model.VBO_vertices(), GL_STATIC_DRAW);
	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexLoc);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.faces().size() * 3 * 3, model.VBO_matdiff(), GL_STATIC_DRAW);
	glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorLoc);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.faces().size() * 3 * 2, model.VBO_uvs(), GL_STATIC_DRAW);
	glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(uvLoc);

	glBindVertexArray(0);
}

void Renderer::LoadTextureFromFile(const string& filename)
{
	GLuint textureID;
	glGenTextures(1, &textureID);  // Genera un ID per la textura

	glActiveTexture(GL_TEXTURE0);  // Activa la unitat de textura 0
	glBindTexture(GL_TEXTURE_2D, textureID);  // Bind la textura

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (!data) {
		cout << "Error carregant textura '" << filename << "': " << stbi_failure_reason() << endl;
		return;
	}
	if (data == nullptr) {
		cout << "Failed to load texture image: " << filename << endl;
		return;
	}
	if (textureID == 0) {
		cout << "Failed to generate texture ID" << endl;
		return;
	}
	cout << "Carregada: " << filename << " (" << width << "x" << height << ", " << nrChannels << " canals)" << endl;

	GLenum internalFormat = 0, dataFormat = 0;
	if (nrChannels == 4) {
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}
	else if (nrChannels == 3) {
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

/*
GLuint Renderer::LoadTextureFromFile(const string& filename) {
	glUseProgram(shaderProgram);

	if (!glIsProgram(shaderProgram)) {
		cout << "shaderProgram NO és un shader vàlid!" << endl;
	}

	if (!glfwGetCurrentContext()) {
		cout << "ERROR: No OpenGL context current!" << endl;
	}

	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		cout << "OpenGL error abans de crear textura: " << err << endl;
	}

	cout << "Hey";
	GLuint textureID;
	glGenTextures(1, &textureID);

	if (textureID == 0) {
		cout << "glGenTextures ha retornat 0!" << endl;
		return 0;
	}

	int width, height, nrChannels;
	cout << "Hey";
	stbi_set_flip_vertically_on_load(true);
	cout << "Hey";
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (!data) {
		cout << "Error carregant textura '" << filename << "': " << stbi_failure_reason() << endl;
		return 0;
	}
	cout << "Carregada: " << filename << " (" << width << "x" << height << ", " << nrChannels << " canals)" << endl;
	cout << "Hey";
	GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	err = glGetError();
	if (err != GL_NO_ERROR) {
		cout << "OpenGL error després de glTexImage2D: " << err << endl;
	}
	/*

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
	return textureID;
}
*/

void Renderer::RenderObject(GameObject* gameObject) 
{
	glUseProgram(shaderProgram);

	string modelName = gameObject->ModelName();
	if (modelVAOs.find(modelName) == modelVAOs.end()) return;
	GLuint VAO = modelVAOs[modelName].first;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureLoc);
	glUniform1i(glGetUniformLocation(shaderProgram, "textureSampler"), 0);

	TransformObject(gameObject->Position(), gameObject->Rotation(), gameObject->Scale());
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, modelVAOs[modelName].second * 3);

	glBindVertexArray(0);
}

void Renderer::TransformObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) 
{
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, position);
	transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	transform = glm::scale(transform, scale);
	glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &transform[0][0]);
}

void Renderer::CameraViewMatrix(const glm::mat4 VM, const glm::mat4 PM) 
{
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &VM[0][0]);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &PM[0][0]);
}

void Renderer::DeleteRenderer() 
{
	glDeleteProgram(shaderProgram);
}

void Renderer::ClearRenderer() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

bool Renderer::LoadShader(const string& shaderToLoad, GLuint &shader)
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

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}