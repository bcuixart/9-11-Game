#ifndef PLANE_HH
#define PLANE_HH

#include <glm/vec3.hpp>
#include <string>
#include <iostream>

#include "GameObject.hh"

using namespace std;

class Plane : public GameObject {
public:
	Plane(const string& _mod, const string& _tex, const string& _sha, int _texType, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl);

	virtual void Update();

	virtual float StaminaPercentage() const;

protected:

private:

	const float PLANE_SPEED = 0.025;
	const float PLANE_SPEED_RUN = 0.075;
	const float PLANE_TURN_SPEED = 0.1;

	const float PLANE_MAX_STAMINA = 10;
	const float PLANE_STAMINA_DEPLETE_SPEED = 0.013;
	const float PLANE_STAMINA_GAIN_SPEED = 0.01;

	float stamina = PLANE_MAX_STAMINA;
	bool staminaDepleted = false;
};

#endif