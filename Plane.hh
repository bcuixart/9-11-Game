#ifndef PLANE_HH
#define PLANE_HH

#include <glm/vec3.hpp>
#include <string>
#include <iostream>

#include "GameObject.hh"

using namespace std;

class Plane : public GameObject {
public:
	Plane(const string& _mod, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl);

	virtual void Update();

protected:

private:
};

#endif