#pragma once

#include <vector>
#include "GameObject.h"
#include "Transform.h"
#include "Collider.h"

class PhysicsManager : public Updateable {
private:
	static PhysicsManager* instance;
	std::map<int, GameObject*> _sceneObjects;
	std::vector<Collider*> _sceneColliders;
	float checkCollision(Transform* obj1, Transform* obj2);
public:
	static PhysicsManager* GetInstance();
	void OnUpdate(int ticks);
	void OnStart();
	void OnEnd();
	void addCollider(Collider* c);
	void removeCollider(Collider* c);
	void Purge();
};