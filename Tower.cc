#include "Tower.hh"
#include "GameManager.hh"

Tower::Tower(const string& _mod, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl)
    : GameObject(_mod, _pos, _rot, _scl)
{
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

    // MOVE TOWER N
    if (alive) {
        if (canMove && distance < TOWER_MOVE_DISTANCE) {
            position += planeToTowerVector * TOWER_MOVE_SPEED;

            
            //if (tower_Height_Lerp == 0) sound_Tower_Jump->play();
            tower_Height_Lerp += TOWER_HEIGHT_INCREMENT;
            if (tower_Height_Lerp > 1) {
                //sound_Tower_Thud->play();
                tower_Height_Lerp = 0;
            }
        }
        else {
            if (tower_Height_Lerp > 0) tower_Height_Lerp += TOWER_HEIGHT_INCREMENT;
            if (tower_Height_Lerp > 1) {
                //sound_Tower_Thud->play();
                tower_Height_Lerp = 0;
            }
        }
    }
    else {
        //tower_Height_Lerp -= TOWER_HEIGHT_INCREMENT;
    }

    position.y = -TOWER_HEIGHT_JUMP_HEIGHT * tower_Height_Lerp * (tower_Height_Lerp - 1);
}