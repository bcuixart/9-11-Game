#include "main.hh"

using namespace std;

void framebufferResizeCallback(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight) 
{
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);
}

int main() 
{
	// Init GLFW
	glfwInit();

	// Create window
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// For MAC users
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME, NULL, NULL);

	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

	glfwMakeContextCurrent(window);

	// Init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		cout << "ERROR: Glew failed to initialize" << endl;
		glfwTerminate();
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Renderer* renderer = new Renderer();
	if (!renderer->initializeRenderer()) {
		glfwTerminate();
	}

	GameManager* gameManager = new GameManager(renderer, window);

	glClearColor(0.5, 0.7, 1.0, 1.0);
	while (!glfwWindowShouldClose(window)) {
		// Input
		glfwPollEvents();

		// Update
		gameManager->Update();

		// Clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Draw


		// End drawing
		glfwSwapBuffers(window);
		glFlush();
	}

	glfwDestroyWindow(window);
	renderer->deleteRenderer();
	glfwTerminate();

}