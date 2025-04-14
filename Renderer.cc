#include "Renderer.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Renderer::Renderer()
{
}

bool Renderer::InitializeRenderer() 
{
	bool lS = LoadShader(SHADER_TO_LOAD, shaderProgram);

	glUseProgram(shaderProgram);

	projLoc = glGetUniformLocation(shaderProgram, "PM");
	viewLoc = glGetUniformLocation(shaderProgram, "VM");
	uvLoc = glGetAttribLocation(shaderProgram, "uv");
	vertexLoc = glGetAttribLocation(shaderProgram, "vertex");
	colorLoc = glGetAttribLocation(shaderProgram, "color");
	TGLoc = glGetUniformLocation(shaderProgram, "TG");
	textureLoc = glGetUniformLocation(shaderProgram, "textureSampler");

	LoadTextureFromFile("./Assets/Textures/Texture_Tower.jpg");

	return lS;
}

void Renderer::InitializeObjectModelVAO(GameObject* gameObject) 
{
	string modelName = gameObject->ModelName();
	if (modelVAOs.find(modelName) != modelVAOs.end()) return;

	vector<float> vertices;

	tinyobj::attrib_t attributes;
	vector<tinyobj::shape_t> shapes;
	vector<tinyobj::material_t> materials;
	string warning, error;

	if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, modelName.c_str())) {
		cout << "Error loading model: " << error << ". Warning: " << warning << endl;
	}

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {

			glm::vec4 pos = {
				attributes.vertices[3 * index.vertex_index],
				attributes.vertices[3 * index.vertex_index + 1],
				attributes.vertices[3 * index.vertex_index + 2],
				1
			};

			glm::vec3 color = { 1.0f, 1.0f, 1.0f };
			if (!attributes.colors.empty()) {
				color = {
					attributes.colors[3 * index.vertex_index],
					attributes.colors[3 * index.vertex_index + 1],
					attributes.colors[3 * index.vertex_index + 2]
				};
			}

			glm::vec2 texcoord = { 0.0f, 0.0f };
			if (index.texcoord_index >= 0) {
				texcoord = {
					attributes.texcoords[2 * index.texcoord_index],
					1 - attributes.texcoords[2 * index.texcoord_index + 1]
				};
			}

			vertices.push_back(pos.x);
			vertices.push_back(pos.y);
			vertices.push_back(pos.z);
			vertices.push_back(color.x);
			vertices.push_back(color.y);
			vertices.push_back(color.z);
			vertices.push_back(texcoord.x);
			vertices.push_back(texcoord.y);
		}
	}

	glGenVertexArrays(1, &modelVAOs[modelName].first);
	glBindVertexArray(modelVAOs[modelName].first);
	modelVAOs[modelName].second = int(vertices.size() / 8);

	int vertexSize = 8 * sizeof(float);
	int vertexCount = int(vertices.size()) / 8;

	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)0);
	glEnableVertexAttribArray(vertexLoc);

	glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(colorLoc);

	glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(uvLoc);

	glBindVertexArray(0);
}

void Renderer::LoadTextureFromFile(const string& filename)
{
	glGenTextures(1, &textureData);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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
	if (textureData == 0) {
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

void Renderer::RenderObject(GameObject* gameObject) 
{
	glUseProgram(shaderProgram);

	string modelName = gameObject->ModelName();
	if (modelVAOs.find(modelName) == modelVAOs.end()) return;
	GLuint VAO = modelVAOs[modelName].first;

	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureData);

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