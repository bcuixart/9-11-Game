#include "Plane.hh"
#include "GameManager.hh"

Plane::Plane(const string& _mod, const string& _tex, const string& _sha, int _texType, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl)
    : GameObject(_mod, _tex, _sha, _texType, _pos, _rot, _scl)
{
}

float Plane::PlaneSpeedPercentage() const
{
    return (currentPlaneSpeed - PLANE_SPEED) / (PLANE_SPEED_RUN - PLANE_SPEED);
}

float Plane::StaminaPercentage() const
{
    return stamina / PLANE_MAX_STAMINA;
}

void Plane::Update()
{
    expectedPlaneSpeed = PLANE_SPEED;
    expectedPlaneTurnSpeed = PLANE_TURN_SPEED;

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
                expectedPlaneSpeed = PLANE_SPEED_RUN;
                expectedPlaneTurnSpeed = PLANE_TURN_SPEED_RUN;
                if (stamina <= 0) {
                    stamina = 0;
                    staminaDepleted = true;
                    expectedPlaneSpeed = PLANE_SPEED;
                    expectedPlaneTurnSpeed = PLANE_TURN_SPEED;
                }
            }
        }
    }
    
    if (abs(expectedPlaneSpeed - currentPlaneSpeed) > PLANE_SPEED_TOLERANCE) 
    {
        if (expectedPlaneSpeed > currentPlaneSpeed) currentPlaneSpeed += PLANE_SPEED_GAIN;
        else currentPlaneSpeed -= PLANE_SPEED_GAIN;
    }

    if (abs(expectedPlaneTurnSpeed - currentPlaneTurnSpeed) > PLANE_TURN_SPEED_TOLERANCE)
    {
        if (expectedPlaneTurnSpeed > currentPlaneTurnSpeed) currentPlaneTurnSpeed += PLANE_TURN_SPEED_GAIN;
        else currentPlaneTurnSpeed -= PLANE_TURN_SPEED_GAIN;
    }

    float rotacioRadians = glm::radians(rotation.y);

    position = position + glm::vec3(
        cos(rotacioRadians),
        0,
        -sin(rotacioRadians)
    ) * currentPlaneSpeed;

    if (inCutscene) return;

    if (GameManager::instance->GetInput(GLFW_KEY_D) == GLFW_PRESS) {
        rotation.y -= currentPlaneTurnSpeed;
    }

    if (GameManager::instance->GetInput(GLFW_KEY_A) == GLFW_PRESS) {
        rotation.y += currentPlaneTurnSpeed;
    }
}