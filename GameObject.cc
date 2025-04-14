#include "GameObject.hh"
#include "GameManager.hh"

void GameObject::Update() 
{
}

void GameObject::OtherTowerHit()
{
}

string GameObject::ModelName() const 
{
	return modelName;
}

string GameObject::TextureName() const
{
	return textureName;
}

int GameObject::TextureType() const 
{
	return textureType;
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

GameObject::GameObject(const string& _mod, const string& _tex, int _texType, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl)
{
	modelName = _mod;
	textureName = _tex;
	textureType = _texType;

	position = _pos;
	rotation = _rot;
	scale = _scl;
}