#include "GameObject.hh"

void GameObject::Update() 
{
	std::cout << "Hola" << std::endl;
}

string GameObject::ModelName() const 
{
	return modelName;
}

glm::vec3 GameObject::Position() const
{
	return position;
}

glm::vec3 GameObject::Rotation() const
{
	return rotation;
}

glm::vec3 GameObject::Scale() const
{
	return scale;
}

GameObject::GameObject(const string& _mod, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl)
{
	modelName = _mod;

	position = _pos;
	rotation = _rot;
	scale = _scl;
}