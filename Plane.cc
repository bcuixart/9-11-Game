#include "Plane.hh"
#include "GameManager.hh"

Plane::Plane(const string& _mod, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl)
    : GameObject(_mod, _pos, _rot, _scl) 
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


    cout << GameManager::instance->GetInput(GLFW_KEY_ESCAPE);
}