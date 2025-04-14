#include "Tower.hh"
#include "GameManager.hh"

Tower::Tower(const string& _mod, const string& _tex, int _texType, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl)
    : GameObject(_mod, _tex, _texType, _pos, _rot, _scl)
{
}

bool Tower::isPlaneInTower(glm::vec3 planePosition) 
{
    float xMin = position.x + tower_Bend.x - HITBOXSIZE / 2;
    float xMax = position.x + tower_Bend.x + HITBOXSIZE / 2;
    float zMin = position.z + tower_Bend.z - HITBOXSIZE / 2;
    float zMax = position.z + tower_Bend.z + HITBOXSIZE / 2;

    return planePosition.x > xMin && planePosition.x < xMax &&
        planePosition.z > zMin && planePosition.z < zMax;
}

void Tower::OtherTowerHit() 
{
    if (alive) {
        canMove = false;
        canBend = true;
    }
}

void Tower::PlayRandomSound(const string* sounds)
{
    int index = GameManager::instance->RNG() % 5;
    GameManager::instance->PlayAudio3D(sounds[index], position, false);
}

void Tower::Update()
{
    GameObject* plane = GameManager::instance->planeGameObject;

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(plane->Rotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 forwardVector = glm::vec3(rotationMatrix * glm::vec4(1, 0, 0, 1));
    glm::vec3 leftVector = glm::normalize(glm::cross(glm::vec3(0, 1, 0), forwardVector));
    glm::vec3 rightVector = -leftVector;
    glm::vec3 planeToTowerVector = position - plane->Position();
    planeToTowerVector.y = 0;

    float distance = glm::distance(position, plane->Position());

    bool inCutscene = GameManager::instance->inCutscene;

    // MOVE TOWER
    if (alive && !inCutscene) {
        if (canMove && distance < TOWER_MOVE_DISTANCE) {
            position += planeToTowerVector * TOWER_MOVE_SPEED;
            
            if (tower_Height_Lerp == 0) PlayRandomSound(jumpSounds);
            tower_Height_Lerp += TOWER_HEIGHT_INCREMENT;
            if (!playedThudSound && tower_Height_Lerp > 0.8) {
                playedThudSound = true;
                PlayRandomSound(thudSounds);
            }
            if (tower_Height_Lerp > 1) {
                playedThudSound = false;
                tower_Height_Lerp = 0;
            }
        }
        else {
            if (tower_Height_Lerp > 0) tower_Height_Lerp += TOWER_HEIGHT_INCREMENT;
            if (!playedThudSound && tower_Height_Lerp > 0.8) {
                playedThudSound = true;
                PlayRandomSound(thudSounds);
            }
            if (tower_Height_Lerp > 1) {
                playedThudSound = false;
                tower_Height_Lerp = 0;
            }
        }
    }
    else if (!alive) {
        tower_Height_Lerp -= TOWER_HEIGHT_INCREMENT;
    }

    // BEND TOWER
    if (alive && !inCutscene && canBend && distance < TOWER_BEND_DISTANCE) {
        glm::vec3 possibleBendPos_1 = position + rightVector * TOWER_BEND_MAGNITUDE_MAX;
        glm::vec3 possibleBendPos_2 = position + leftVector * TOWER_BEND_MAGNITUDE_MAX;

        float dist1 = glm::distance(plane->Position(), possibleBendPos_1);
        float dist2 = glm::distance(plane->Position(), possibleBendPos_2);
        if (dist1 >= dist2) tower_Expected_Bend = glm::cross(forwardVector, glm::vec3(0, 1, 0)) * TOWER_BEND_MAGNITUDE_MAX;
        else tower_Expected_Bend = glm::cross(forwardVector, glm::vec3(0, -1, 0)) * TOWER_BEND_MAGNITUDE_MAX;
    }
    else {
        tower_Expected_Bend = glm::vec3(0,0,0);
    }

    tower_Bend =
        glm::vec3(abs(tower_Bend.x - tower_Expected_Bend.x) < TOWER_BEND_SNAP ? tower_Expected_Bend.x :
            (tower_Bend.x > tower_Expected_Bend.x ? tower_Bend.x - TOWER_BEND_SPEED : tower_Bend.x + TOWER_BEND_SPEED),
            0,
            abs(tower_Bend.z - tower_Expected_Bend.z) < TOWER_BEND_SNAP ? tower_Expected_Bend.z :
            (tower_Bend.z > tower_Expected_Bend.z ? tower_Bend.z - TOWER_BEND_SPEED : tower_Bend.z + TOWER_BEND_SPEED));


    if (alive && !inCutscene && isPlaneInTower(plane->Position())) {
        alive = false;

        GameManager::instance->TowerHit(this);
    }

    position.y = TOWER_HEIGHT_JUMP_HEIGHT * tower_Height_Lerp * (tower_Height_Lerp - 1) * (tower_Height_Lerp - .8);
}