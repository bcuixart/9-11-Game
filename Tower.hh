#ifndef TOWER_HH
#define TOWER_HH

#include <glm/vec3.hpp>
#include <string>
#include <iostream>

#include "GameObject.hh"

using namespace std;

class Tower : public GameObject {
public:
	Tower(const string& _mod, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl);

	virtual void Update();

protected:

private:

	bool alive = true;

	bool canMove = true;
	bool canBend = false;

	const float TOWER_MOVE_SPEED = 0.001;
	const float TOWER_MOVE_DISTANCE = 40;
	const float TOWER_HEIGHT_INCREMENT = 0.01;
	const float TOWER_HEIGHT_JUMP_HEIGHT = 5;
	float tower_Height_Lerp = 0;
};

#endif