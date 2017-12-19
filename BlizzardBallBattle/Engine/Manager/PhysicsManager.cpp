
#include "PhysicsManager.h"
#include <stdio.h>
#include <cmath>
#include "SceneManager.h"
#include <algorithm>

PhysicsManager* PhysicsManager::instance;

PhysicsManager* PhysicsManager::GetInstance() {
	if (instance == NULL)
		instance = new PhysicsManager();
	return instance;
}

void PhysicsManager::OnStart() {
	//load gameobjects in scene into vector list
	_sceneObjects = SceneManager::GetInstance()->GetCurrentScene()->sceneObjects;
}

void PhysicsManager::OnUpdate(int ticks) {

	//TODO: change to iterators by beta or release
	if (_sceneColliders.size() > 1) {
		for (int i = 0; i < _sceneColliders.size(); i++) {
			_sceneColliders[i]->clearColliders();
			_sceneColliders[i]->setCollision(false);
		}
		for (int i = 0; i < _sceneColliders.size() - 1; i++) {
			for (int j = i + 1; j < _sceneColliders.size(); j++) {
				Collider* c1 = _sceneColliders[i];
				Collider* c2 = _sceneColliders[j];

				if (checkCollision(c1->getTransform(), c2->getTransform()) < (c1->getRadius()-0.2f + c2->getRadius())) {
					c1->getTransform()->getY();
					c1->addCollision(c2->GetGameObject());
					c1->setCollision(true);
					c2->setCollision(true);
					c2->addCollision(c1->GetGameObject());
				}
			}
		}
	}
}

void PhysicsManager::addCollider(Collider* c) {
	_sceneColliders.push_back(c);
}

void PhysicsManager::removeCollider(Collider* c) {
	_sceneColliders.erase(std::remove(_sceneColliders.begin(), _sceneColliders.end(), c), _sceneColliders.end());
}

void PhysicsManager::OnEnd() {

}

float PhysicsManager::checkCollision(Transform* obj1, Transform* obj2) {
	return sqrt(pow(obj1->getX() - obj2->getX(), 2) + pow(obj1->getY() - obj2->getY(),2));
}

void PhysicsManager::Purge() {
	_sceneColliders.clear();
}