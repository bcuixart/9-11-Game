#include "StaminaBar.hh"
#include "GameManager.hh"

StaminaBar::StaminaBar(const string& _mod, const string& _tex, const string& _sha, int _texType, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl)
    : GameObject(_mod, _tex, _sha, _texType, _pos, _rot, _scl)
{
    defaultPosition = _pos;
    defaultScale = _scl;
}


void StaminaBar::Update()
{
    float percentage = GameManager::instance->planeGameObject->StaminaPercentage();

    scale.x = defaultScale.x * percentage;
    position.x = defaultPosition.x - (defaultScale.x / 2) * (1-percentage);
}