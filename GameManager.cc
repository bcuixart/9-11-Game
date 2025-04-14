#include "GameManager.hh"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager(Renderer* _renderer, GLFWwindow* _window)
{
	renderer = _renderer;
	window = _window;

	GameManager::instance = this;
}

int GameManager::GetInput(int key) 
{
	return glfwGetKey(window, key);
}

/*
void GameManager::GetInput() 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		cout << "Wow, you pressed a key, so proud." << endl;
	}
}
*/

void GameManager::TowerHit(GameObject* tower) 
{
	cout << "Cutscene start" << endl;
	cutscene_Left_Time = CUTSCENE_DURATION;
	cutsceneLookAt = tower->Position();
	inCutscene = true;

	if (tower == towerNGameObject) towerSGameObject->OtherTowerHit();
	if (tower == towerSGameObject) towerNGameObject->OtherTowerHit();
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
	renderer->InitializeObjectModelTexture(gameObject);
}

void GameManager::Update() 
{
	renderer->ClearRenderer();
	renderer->CameraViewMatrix(camera->GetCameraViewMatrix(), camera->GetCameraProjectMatrix());

	for (auto it = currentGameObjects.begin(); it != currentGameObjects.end(); ++it) {
		(*it)->Update();
	}

	for (auto it = currentGameObjects.begin(); it != currentGameObjects.end(); ++it) {
		renderer->RenderObject(*it);
	}

	if (inCutscene) {
		--cutscene_Left_Time;

		if (cutscene_Left_Time < 0) {
			cout << "Cutscene end" << endl;
			inCutscene = false;
		}

		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(planeGameObject->Rotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::vec3 forwardVector = glm::vec3(rotationMatrix * glm::vec4(1, 0, 0, 1));

		glm::vec3 cutscenePos = cutsceneLookAt - CUTSCENE_CAMERA_DISTANCE * forwardVector;
		cutscenePos.y = 35;
		camera->MoveCamera(cutscenePos);
		camera->RotateCamera(planeGameObject->Rotation() + glm::vec3(-20, -90, 0));
	}
	else {
		camera->MoveCamera(planeGameObject->Position());
		camera->RotateCamera(planeGameObject->Rotation() + glm::vec3(0, -90, 0));
	}
}