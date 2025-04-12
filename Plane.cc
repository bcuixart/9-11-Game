#include "Plane.hh"

void Plane::Update()
{
	std::cout << "Hola soc un avio" << std::endl;
}

Plane::Plane(const string& _mod, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl)
    : GameObject(_mod, _pos, _rot, _scl)  // Call to base class constructor
{
    // Additional initialization for Plane, if needed
}