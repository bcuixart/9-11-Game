#ifndef TOWER_HH
#define TOWER_HH

#define FRAMERATESCALEFATOR 300

#include <glm/vec3.hpp>
#include <string>
#include <iostream>

#include "GameObject.hh"

using namespace std;

class Tower : public GameObject {
public:
	Tower(const string& _mod, const string& _tex, const string& _sha, int _texType, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl);

	virtual void Update();

	virtual void OtherTowerHit();

protected:

private:

	bool alive = true;

	bool canMove = true;
	bool canBend = false;

	const float TOWER_MOVE_SPEED = 0.00215 * FRAMERATESCALEFATOR;
	//const float TOWER_MOVE_SPEED = 0.00025;
	const float TOWER_MOVE_DISTANCE = 40;
	const float TOWER_HEIGHT_INCREMENT = 0.005 * FRAMERATESCALEFATOR;
	const float TOWER_HEIGHT_JUMP_HEIGHT = 5;
	float tower_Height_Lerp = 0;
	bool playedThudSound = false;

	const float TOWER_BEND_MAGNITUDE_MAX = 12;
	const float TOWER_BEND_SPEED = 0.16 * FRAMERATESCALEFATOR;
	const float TOWER_BEND_DISTANCE = 35;
	const float TOWER_BEND_SNAP = .5;

	const float HITBOXSIZE = 6.3;

	glm::vec3 tower_Bend_Old = glm::vec3(0, 0, 0);

	bool isPlaneInTower(glm::vec3 planePosition);

	void PlayRandomSound(const string* sounds);

	const string jumpSounds[5] = {
		"./Assets/Audio/Audio_Tower_Jump001.ogg",
		"./Assets/Audio/Audio_Tower_Jump002.ogg",
		"./Assets/Audio/Audio_Tower_Jump003.ogg",
		"./Assets/Audio/Audio_Tower_Jump004.ogg",
		"./Assets/Audio/Audio_Tower_Jump005.ogg"
	};

	const string thudSounds[5] = {
		"./Assets/Audio/Audio_Tower_Thud001.ogg",
		"./Assets/Audio/Audio_Tower_Thud002.ogg",
		"./Assets/Audio/Audio_Tower_Thud003.ogg",
		"./Assets/Audio/Audio_Tower_Thud004.ogg",
		"./Assets/Audio/Audio_Tower_Thud005.ogg"
	};

	const string bendSounds[5] = {
		"./Assets/Audio/Audio_Tower_Bend001.ogg",
		"./Assets/Audio/Audio_Tower_Bend002.ogg",
		"./Assets/Audio/Audio_Tower_Bend003.ogg",
		"./Assets/Audio/Audio_Tower_Bend004.ogg",
		"./Assets/Audio/Audio_Tower_Bend005.ogg"
	};

	const string retractSounds[5] = {
		"./Assets/Audio/Audio_Tower_Retract001.ogg",
		"./Assets/Audio/Audio_Tower_Retract002.ogg",
		"./Assets/Audio/Audio_Tower_Retract003.ogg",
		"./Assets/Audio/Audio_Tower_Retract004.ogg",
		"./Assets/Audio/Audio_Tower_Retract005.ogg"
	};
};

#endif