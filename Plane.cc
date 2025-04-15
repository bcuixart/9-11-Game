#include "Plane.hh"
#include "GameManager.hh"

Plane::Plane(const string& _mod, const string& _tex, const string& _sha, int _texType, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl)
    : GameObject(_mod, _tex, _sha, _texType, _pos, _rot, _scl)
{
}

float Plane::StaminaPercentage() const
{
    return stamina / PLANE_MAX_STAMINA;
}

void Plane::Update()
{
    float currentSpeed = PLANE_SPEED;

    bool inCutscene = GameManager::instance->inCutscene;

    if (!inCutscene) {
        if (staminaDepleted)
        {
            stamina += PLANE_STAMINA_GAIN_SPEED;
            if (stamina >= PLANE_MAX_STAMINA) {
                stamina = PLANE_MAX_STAMINA;
                staminaDepleted = false;
            }
        }
        else {
            if (GameManager::instance->GetInput(GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                stamina -= PLANE_STAMINA_DEPLETE_SPEED;
                currentSpeed = PLANE_SPEED_RUN;
                if (stamina <= 0) {
                    stamina = 0;
                    staminaDepleted = true;
                    currentSpeed = PLANE_SPEED;
                }
            }
        }
    }


    float rotacioRadians = glm::radians(rotation.y);

    position = position + glm::vec3(
        cos(rotacioRadians),
        0,
        -sin(rotacioRadians)
    ) * currentSpeed;

    if (inCutscene) return;

    if (GameManager::instance->GetInput(GLFW_KEY_D) == GLFW_PRESS) {
        rotation.y -= PLANE_TURN_SPEED;
    }

    if (GameManager::instance->GetInput(GLFW_KEY_A) == GLFW_PRESS) {
        rotation.y += PLANE_TURN_SPEED;
    }
}