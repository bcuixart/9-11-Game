#ifndef GAMEMANAGER_HH
#define GAMEMANAGER_HH

#include <vector>
#include <list>

#include "Renderer.hh"
#include "GameObject.hh"
#include "Plane.hh"
#include "Camera.hh"

using namespace std;

class GameManager {
public:
	GameManager(Renderer* _renderer, GLFWwindow* _window);

	static GameManager* instance;

	void Start();
	void Update();

	void InstantiateGameObject(GameObject* gameObject);

private:
	Renderer* renderer;
	Camera* camera;
	GLFWwindow* window;

	void GetInput();

	list<GameObject*> currentGameObjects;

	GameObject* planeGameObject = new Plane("./Assets/Models/Plane.obj", glm::vec3(0, 30, 0), glm::vec3(0), glm::vec3(1));

	vector<GameObject*> initialGameObjects = {
		new GameObject("./Assets/Models/Tower_N.obj", glm::vec3(6.4,0,0), glm::vec3(0), glm::vec3(1)),
		new GameObject("./Assets/Models/Tower_S.obj", glm::vec3(-6.4,0,0), glm::vec3(0), glm::vec3(1)),
		planeGameObject
	};
};

#endif