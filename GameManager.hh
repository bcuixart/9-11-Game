#ifndef GAMEMANAGER_HH
#define GAMEMANAGER_HH

#include <vector>
#include <list>

#include <cstdlib>
#include <ctime>

#include "Renderer.hh"
#include "AudioEngine.hh"
#include "Camera.hh"
#include "GameObject.hh"
#include "Plane.hh"
#include "Tower.hh"

using namespace std;

class GameManager {
public:
	GameManager(Renderer* _renderer, AudioEngine* _audioEngine, GLFWwindow* _window);

	static GameManager* instance;

	void Start();
	void Update();

	int GetInput(int key);

	void InstantiateGameObject(GameObject* gameObject);

	int RNG();

	void PlayAudio(const string& audioName, bool loop);
	void PlayAudio3D(const string& audioName, const glm::vec3 position, bool loop);

	GameObject* planeGameObject = new Plane("./Assets/Models/Plane_Interior.obj", "./Assets/Textures/Plane_Interior.png", GL_MIRRORED_REPEAT, glm::vec3(0, 30, -100), glm::vec3(0, -90, 0), glm::vec3(1));
	GameObject* planeGameObjectOutside = new Plane("./Assets/Models/Plane.obj", "./Assets/Textures/Plane.png", GL_MIRRORED_REPEAT, glm::vec3(0, 30, -100), glm::vec3(0, -90, 0), glm::vec3(1));

	void TowerHit(GameObject* tower);

	bool inCutscene = false;

private:
	Renderer* renderer;
	AudioEngine* audioEngine;
	Camera* camera;
	GLFWwindow* window;

	list<GameObject*> currentGameObjects;

	GameObject* towerNGameObject = new Tower("./Assets/Models/Tower_N.obj", "./Assets/Textures/Texture_Tower.jpg", GL_REPEAT, glm::vec3(-4, 0, -3.15), glm::vec3(0), glm::vec3(1));
	GameObject* towerSGameObject = new Tower("./Assets/Models/Tower_S.obj", "./Assets/Textures/Texture_Tower.jpg", GL_REPEAT, glm::vec3(4, 0, 3.15), glm::vec3(0), glm::vec3(1));

	vector<GameObject*> initialGameObjects = {
		towerNGameObject,
		towerSGameObject,
		planeGameObject,
		planeGameObjectOutside,
		new GameObject("./Assets/Models/CityGround.obj", "./Assets/Textures/Texture_City.png", GL_REPEAT, glm::vec3(0, 0, 0), glm::vec3(0), glm::vec3(1))
	};

	const float CUTSCENE_DURATION = 1000;
	const float CUTSCENE_CAMERA_DISTANCE = 20;
	float cutscene_Left_Time = 0;
	glm::vec3 cutsceneLookAt;
};

#endif