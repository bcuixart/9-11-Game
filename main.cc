#include "main.hh"

using namespace std;
using namespace chrono;

void framebufferResizeCallback(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight) 
{
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);
	renderer->InitializeRenderer(frameBufferWidth, frameBufferHeight);
}

int main(int argc, char* argv[]) 
{
	if (argc == 2) {
		if (strcmp(argv[1], "-f") == 0) {
			showFPS = true;
		}
	}

	// Init GLFW
	glfwInit();

	// Create window
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// For MAC users
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME, NULL, NULL);

	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

	glfwMakeContextCurrent(window);

	glViewport(0, 0, WIDTH, HEIGHT);

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

	renderer = new Renderer();
	if (!renderer->InitializeRenderer(WIDTH, HEIGHT)) {
		cout << "ERROR: Renderer failed to initialize" << endl;
		glfwTerminate();
	}

	AudioEngine* audioEngine = new AudioEngine();
	if (!audioEngine->InitializeAudioEngine()) {
		cout << "ERROR: Audio engine failed to initialize" << endl;
		glfwTerminate();
	}

	GameManager* gameManager = new GameManager(renderer, audioEngine, window);
	gameManager->Start();

	glClearColor(0.5, 0.7, 1.0, 1.0);
	while (!glfwWindowShouldClose(window)) 
	{
		auto frameStart = high_resolution_clock::now();

		// Input
		glfwPollEvents();

		// Update
		gameManager->Update(deltaTime);

		// End drawing
		glfwSwapBuffers(window);
		glFlush();

		auto frameEnd = high_resolution_clock::now();
		deltaTime = duration<float>(frameEnd - frameStart).count();

		if (deltaTime < DESIRED_FRAME_TIME) {
			std::this_thread::sleep_for(duration<float>(DESIRED_FRAME_TIME - deltaTime));

			frameEnd = high_resolution_clock::now();
			deltaTime = duration<float>(frameEnd - frameStart).count();
		}

		fps = 1.0f / deltaTime;
		if (showFPS) cerr << fps << " FPS" << endl;
	}

	glfwDestroyWindow(window);
	renderer->DeleteRenderer();
	audioEngine->DeleteAudioEngine();
	glfwTerminate();

}