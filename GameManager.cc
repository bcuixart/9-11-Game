#include "GameManager.hh"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager(Renderer* _renderer, AudioEngine* _audioEngine, GLFWwindow* _window)
{
	renderer = _renderer;
	audioEngine = _audioEngine;
	window = _window;

	GameManager::instance = this;
}

void GameManager::UpdateCamera() 
{
	if (inCutscene) {
		cutscene_Left_Time -= deltaTime;

		if (cutscene_Left_Time < 0) {
			inCutscene = false;

			++towersTakenDown;
			if (towersTakenDown == 2) PlayAudio("./Assets/Audio/Audio_Victory.ogg", true);
		}

		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(planeGameObject->Rotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::vec3 forwardVector = glm::vec3(rotationMatrix * glm::vec4(1, 0, 0, 1));

		glm::vec3 cutscenePos = cutsceneLookAt - CUTSCENE_CAMERA_DISTANCE * forwardVector;
		cutscenePos.y = 35;
		camera->MoveCamera(cutscenePos);
		cameraPosition = cutscenePos;
		camera->RotateCamera(planeGameObject->Rotation() + glm::vec3(-20, -90, 0));
	}
	else
	{
		camera->MoveCamera(planeGameObject->Position());
		cameraPosition = planeGameObject->Position();
		camera->RotateCamera(planeGameObject->Rotation() + glm::vec3(0, -90, 0));
	}

	renderer->CameraFogPos(cameraPosition);
	renderer->CameraViewMatrix(camera->GetCameraViewMatrix(), camera->GetCameraProjectMatrix());
}

void GameManager::UpdateAudioEngine() 
{
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(planeGameObject->Rotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 forwardVector = glm::vec3(rotationMatrix * glm::vec4(1, 0, 0, 1));

	float cameraPos[] = { cameraPosition.x, cameraPosition.y, cameraPosition.z };
	float cameraForward[] = { forwardVector.x, forwardVector.y, forwardVector.z };
	audioEngine->Update(cameraPos, cameraForward);

	SetAudioSpeed(planeSound, 1 + planeGameObject->PlaneSpeedPercentage() * 0.25);
}

int GameManager::GetInput(int key) 
{
	return glfwGetKey(window, key);
}

ALuint GameManager::PlayAudio(const string& audioName, bool loop)
{
	return audioEngine->PlayAudio(audioName, loop);
}

ALuint GameManager::PlayAudio3D(const string& audioName, const glm::vec3 position, bool loop)
{
	ALfloat pos[] = { position.x, position.y, position.z };
	return audioEngine->PlayAudio3D(audioName, pos, loop);
}

void GameManager::SetAudioSpeed(ALuint source, float speed)
{
	audioEngine->SetAudioSpeed(source, speed);
}

void GameManager::TowerHit(GameObject* tower) 
{
	PlayAudio3D("./Assets/Audio/Audio_Tower_Impact.ogg", tower->Position(), false);

	cutscene_Left_Time = CUTSCENE_DURATION;
	cutsceneLookAt = tower->Position();
	inCutscene = true;

	if (tower == towerNGameObject) towerSGameObject->OtherTowerHit();
	if (tower == towerSGameObject) towerNGameObject->OtherTowerHit();
}

void GameManager::Start() 
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	camera = new Camera(glm::vec3(0,100,50), glm::vec3(-45,0,0), 45, 1, 0.1, 1000000);

	InstantiateScreen(screenQuadObject);

	int sz = (int)initialGameObjects.size();
	for (int i = 0; i < sz; ++i)
	{
		InstantiateGameObject(initialGameObjects[i]);
	}

	int szUI = (int)initialUIObjects.size();
	for (int i = 0; i < szUI; ++i)
	{
		InstantiateUIObject(initialUIObjects[i]);
	}

	planeSound = PlayAudio("./Assets/Audio/Audio_Plane_Loop.ogg", true);
}

void GameManager::InstantiateGameObject(GameObject* gameObject) 
{
	currentGameObjects.push_back(gameObject);
	renderer->InitializeObjectModelShader(gameObject);
	renderer->InitializeObjectModelVAO(gameObject);
	renderer->InitializeObjectModelTexture(gameObject);
}

void GameManager::InstantiateUIObject(GameObject* gameObject)
{
	currentUIObjects.push_back(gameObject);
	renderer->InitializeObjectModelShader(gameObject);
	renderer->InitializeObjectModelVAO(gameObject);
	renderer->InitializeObjectModelTexture(gameObject);
}

void GameManager::InstantiateScreen(GameObject* screen) 
{
	renderer->InitializeObjectModelShader(screen);
	renderer->InitializeObjectModelVAO(screen);
	renderer->InitializeObjectModelTexture(screen);
}

int GameManager::RNG() 
{
	return std::rand();
}

float GameManager::DeltaTime() 
{
	return deltaTime;
}

void GameManager::Update(float _dT)
{
	deltaTime = _dT;
	++frameCount;

	renderer->StartFrame();
	renderer->ClearRenderer();

	for (auto it = currentGameObjects.begin(); it != currentGameObjects.end(); ++it) {
		(*it)->Update();
	}

	for (auto it = currentUIObjects.begin(); it != currentUIObjects.end(); ++it) {
		(*it)->Update();
	}

	UpdateAudioEngine();
	UpdateCamera();

	for (auto it = currentGameObjects.begin(); it != currentGameObjects.end(); ++it) {
		renderer->RenderObject(*it);
	}

	renderer->StartUIRender();
	for (auto it = currentUIObjects.begin(); it != currentUIObjects.end(); ++it) {
		renderer->RenderObject(*it);
	}

	renderer->EndFrame();
	renderer->ClearRenderer();

	renderer->RenderScreen(screenQuadObject, frameCount);
}