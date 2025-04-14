#include "Plane.hh"
#include "GameManager.hh"

Plane::Plane(const string& _mod, const string& _tex, int _texType, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl)
    : GameObject(_mod, _tex, _texType, _pos, _rot, _scl)
{
}

void Plane::Update()
{
    float rotacioRadians = glm::radians(rotation.y);

    position = position + glm::vec3(
        cos(rotacioRadians),
        0,
        -sin(rotacioRadians)
    ) * PLANE_SPEED;

    bool inCutscene = GameManager::instance->inCutscene;

    if (inCutscene) return;

    if (GameManager::instance->GetInput(GLFW_KEY_D) == GLFW_PRESS) {
        rotation.y -= PLANE_TURN_SPEED;
    }

    if (GameManager::instance->GetInput(GLFW_KEY_A) == GLFW_PRESS) {
        rotation.y += PLANE_TURN_SPEED;
    }
}