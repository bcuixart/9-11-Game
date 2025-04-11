#ifndef GAMEMANAGER
#define GAMEMANAGER

#include <list>

#include "Renderer.hh"
#include "GameObject.hh"

using namespace std;

class GameManager {
public:
	GameManager(Renderer* _renderer, GLFWwindow* _window);

	void Start();
	void Update();

	void InstantiateGameObject(GameObject* gameObject);

private:
	Renderer* renderer;
	GLFWwindow* window;

	void GetInput();

	list<GameObject> currentGameObjects;

	std::vector<GameObject> initialGameObjects = {
		GameObject("./Assets/Models/Debug_Point.obj", glm::vec3(.1,0,-.5), glm::vec3(0), glm::vec3(1))
	};
};

#endif