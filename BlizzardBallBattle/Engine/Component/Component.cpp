#include "Component.h"
#include "GameManager.h"

Component::Component(GameObject* gameObject) {
   this->gameObject = gameObject;
}

GameObject* Component::GetGameObject() {
 return gameObject;
}

Component::~Component() {}


void Component::Destroy(GameObject* gameObject) {
	GameManager::GetInstance()->RemoveGameObject(gameObject);
}