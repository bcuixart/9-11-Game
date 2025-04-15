#ifndef STAMINA_BAR_HH
#define STAMINA_BAR_HH

#include <glm/vec3.hpp>
#include <string>
#include <iostream>

#include "GameObject.hh"

using namespace std;

class StaminaBar : public GameObject {
public:
	StaminaBar(const string& _mod, const string& _tex, const string& _sha, int _texType, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl);

	virtual void Update();

protected:

private:
	glm::vec3 defaultPosition;
	glm::vec3 defaultScale;
};

#endif