#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include <glm/vec3.hpp>
#include <string>
#include <iostream>

using namespace std;

class GameObject {
public:
	GameObject(const string& _mod, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl);

	string ModelName() const;

	glm::vec3 Position() const;
	glm::vec3 Rotation() const;
	glm::vec3 Scale() const;

	virtual void Update();

protected:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

private:

	string modelName;
};

#endif