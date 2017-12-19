#include "GameObject.h"
#include "Transform.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "GameManager.h"
 
GameObject::GameObject(bool g) {
    id = rand() + rand();
    isGlobal = g;
    if (isGlobal)
        GameManager::GetInstance()->AddGameObject(id, this);
    if (SceneManager::GetInstance()->HasScene())
        SceneManager::GetInstance()->GetCurrentScene()->AddGameObject(id, this);
	transform = new Transform(this);
    AddComponent<Transform*>(transform);
}

void GameObject::OnComponentsUpdate(int ticks) {
    for (std::map<std::string, std::vector<Component*>>::iterator it=components.begin(); it!=components.end(); ++it) {
        for (size_t i = 0; i < it->second.size(); i++){
            it->second[i]->OnUpdate(ticks);
        }
    }
}

GameObject::~GameObject() {
    RemoveAllComponents();
}

Transform* GameObject::GetTransform() {
    return transform;
}


void GameObject::Destroy(GameObject* gameObject) {
	GameManager::GetInstance()->RemoveGameObject(gameObject);
}