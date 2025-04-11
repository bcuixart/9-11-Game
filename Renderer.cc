#include "Renderer.hh"

Renderer::Renderer()
{
}

bool Renderer::initializeRenderer() 
{
	bool lS = loadShader(SHADER_TO_LOAD, shaderProgram);

	projLoc = glGetUniformLocation(shaderProgram, "PM");
	viewLoc = glGetUniformLocation(shaderProgram, "VM");
	vertexLoc = glGetAttribLocation(shaderProgram, "vertex");
	colorLoc = glGetAttribLocation(shaderProgram, "color");
	TGLoc = glGetUniformLocation(shaderProgram, "TG");

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

	GLuint VBOs[2];
	glGenBuffers(2, VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.faces().size() * 3 * 3, model.VBO_vertices(), GL_STATIC_DRAW);

	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexLoc);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * model.faces().size() * 3 * 3, model.VBO_matdiff(), GL_STATIC_DRAW);

	glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorLoc);

	glBindVertexArray(0);
}

void Renderer::RenderObject(GameObject* gameObject) 
{
	glUseProgram(shaderProgram);

	string modelName = gameObject->ModelName();
	if (modelVAOs.find(modelName) == modelVAOs.end()) return;
	GLuint VAO = modelVAOs[modelName].first;

	cout << modelVAOs[modelName].second << endl;
	TransformObject(gameObject->Position(), gameObject->Rotation(), gameObject->Scale());
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, modelVAOs[modelName].second * 3);

	glBindVertexArray(0);

	glUseProgram(0);
}

void Renderer::TransformObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) 
{
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, position);
	transform = glm::rotate(transform, rotation.x, glm::vec3(1, 0, 0));
	transform = glm::rotate(transform, rotation.y, glm::vec3(0, 1, 0));
	transform = glm::rotate(transform, rotation.z, glm::vec3(0, 0, 1));
	transform = glm::scale(transform, scale);
	glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &transform[0][0]);
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