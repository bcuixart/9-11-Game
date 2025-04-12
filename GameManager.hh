#ifndef GAMEMANAGER
#define GAMEMANAGER

#include <list>

#include "Renderer.hh"
#include "GameObject.hh"
#include "Camera.hh"

using namespace std;

class GameManager {
public:
	GameManager(Renderer* _renderer, GLFWwindow* _window);

	void Start();
	void Update();

	void InstantiateGameObject(GameObject* gameObject);

private:
	Renderer* renderer;
	Camera* camera;
	GLFWwindow* window;

	void GetInput();

	list<GameObject> currentGameObjects;

	std::vector<GameObject> initialGameObjects = {
		GameObject("./Assets/Models/Tower_N.obj", glm::vec3(6.4,0,0), glm::vec3(0), glm::vec3(1)),
		GameObject("./Assets/Models/Tower_S.obj", glm::vec3(-6.4,0,0), glm::vec3(0), glm::vec3(1))
	};
};

#endif