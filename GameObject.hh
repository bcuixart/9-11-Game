#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <string>
#include <iostream>

using namespace std;

class GameManager;

class GameObject {
public:
	GameObject(const string& _mod, const string& _tex, const string& _sha, int _texType, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl);
	virtual ~GameObject() = default;

	string ModelName() const;
	string ShaderName() const;
	string TextureName() const;
	int TextureType() const;

	glm::vec3 Position() const;
	glm::vec3 Rotation() const;
	glm::vec3 Scale() const;

	virtual void Update();
	virtual void OtherTowerHit();
	virtual float StaminaPercentage() const;

	glm::vec3 tower_Bend = glm::vec3(0, 0, 0);

protected:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::vec3 tower_Expected_Bend = glm::vec3(0, 0, 0);

private:

	string modelName;
	string shaderName;
	string textureName;
	int textureType;
};

#endif