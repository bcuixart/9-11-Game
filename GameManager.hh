#ifndef GAMEMANAGER_HH
#define GAMEMANAGER_HH

#include <vector>
#include <list>

#include "Renderer.hh"
#include "Camera.hh"
#include "GameObject.hh"
#include "Plane.hh"
#include "Tower.hh"

using namespace std;

class GameManager {
public:
	GameManager(Renderer* _renderer, GLFWwindow* _window);

	static GameManager* instance;

	void Start();
	void Update();

	int GetInput(int key);

	void InstantiateGameObject(GameObject* gameObject);

	GameObject* planeGameObject = new Plane("./Assets/Models/Plane.obj", glm::vec3(0, 30, -50), glm::vec3(0, -90, 0), glm::vec3(1));

private:
	Renderer* renderer;
	Camera* camera;
	GLFWwindow* window;

	list<GameObject*> currentGameObjects;

	GameObject* towerNGameObject = new Tower("./Assets/Models/Tower_N.obj", glm::vec3(-4, 0, -3.15), glm::vec3(0), glm::vec3(1));
	GameObject* towerSGameObject = new Tower("./Assets/Models/Tower_S.obj", glm::vec3(4, 0, 3.15), glm::vec3(0), glm::vec3(1));

	vector<GameObject*> initialGameObjects = {
		towerNGameObject,
		towerSGameObject,
		planeGameObject
	};
};

#endif