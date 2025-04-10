#ifndef GAMEMANAGER
#define GAMEMANAGER

#include "Renderer.hh"

using namespace std;

class GameManager {
public:
	GameManager(Renderer* _renderer, GLFWwindow* _window);

	void Update();

private:
	Renderer* renderer;
	GLFWwindow* window;

	void GetInput();
};

#endif