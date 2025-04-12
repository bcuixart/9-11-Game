#include "GameManager.hh"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager(Renderer* _renderer, GLFWwindow* _window)
{
	renderer = _renderer;
	window = _window;

	GameManager::instance = this;
}

void GameManager::GetInput() 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		cout << "Wow, you pressed a key, so proud." << endl;
	}
}

void GameManager::Start() 
{
	camera = new Camera(glm::vec3(0,100,50), glm::vec3(-45,0,0), 45, 1, 0.1, 100);

	for (int i = 0; i < initialGameObjects.size(); ++i) 
	{
		InstantiateGameObject(initialGameObjects[i]);
	}
}

void GameManager::InstantiateGameObject(GameObject* gameObject) 
{
	currentGameObjects.push_back(gameObject);
	renderer->InitializeObjectModelVAO(gameObject);
}

void GameManager::Update() 
{
	GetInput();

	renderer->ClearRenderer();
	renderer->CameraViewMatrix(camera->GetCameraViewMatrix(), camera->GetCameraProjectMatrix());

	for (auto it = currentGameObjects.begin(); it != currentGameObjects.end(); ++it) {
		(*it)->Update();
	}

	for (auto it = currentGameObjects.begin(); it != currentGameObjects.end(); ++it) {
		renderer->RenderObject(*it);
	}

}