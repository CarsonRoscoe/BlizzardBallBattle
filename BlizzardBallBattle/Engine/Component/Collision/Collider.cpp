#include "Collider.h"
#include "Transform.h"
#include <math.h>
#include "PhysicsManager.h"

Collider::Collider(GameObject* gameObject, float radius) : Component(gameObject) , _radius(radius){
	_collision = false;
	//add to physics manager;
	PhysicsManager::GetInstance()->addCollider(this);
	transform = gameObject->GetComponent<Transform*>();
}

bool Collider::collisionDetected() {
	return _collision;
}

void Collider::setCollision(bool collision) {
	_collision = collision;
}

bool Collider::DoesCollide(GameObject* other) {
	Transform* myTrans = gameObject->GetTransform();
	Transform* otherTrans = other->GetTransform();

	float a = myTrans->getX() - otherTrans->getX();
	float b = myTrans->getY() - otherTrans->getY();
	float c = sqrtf(a * a + b * b);
	float myRad = myTrans->getScale() / 2.0f;
	float otherRad = otherTrans->getScale() / 2.0f;

	return c <= myRad + otherRad;
}

GameObject* Collider::getColliderObj() {
	return _colliderObj;
}

std::vector<GameObject*> Collider::getColliders() {
	return _colliders;
}

void Collider::setColliderObj(GameObject* collider) {
	_colliderObj = collider;
}

void Collider::clearColliders() {
	_colliders.clear();
}

void Collider::addCollision(GameObject* collider) {
	_colliders.push_back(collider);
}

float Collider::getRadius() {
	return _radius;
}

void Collider::setRadius(float radius) {
	_radius = radius;
}

Transform * Collider::getTransform()
{
	return transform;
}

Collider::~Collider() {
	PhysicsManager::GetInstance()->removeCollider(this);
}
