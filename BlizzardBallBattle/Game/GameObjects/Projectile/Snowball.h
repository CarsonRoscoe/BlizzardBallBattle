#pragma once

#include "GameObject.h"
#include "Battler.h"
#include "Collider.h"
#include "SimpleSprite.h"

class Snowball : public SimpleSprite {
private:
	bool active;
	GameObject* _player;
	float _speed;
	Collider* myCollider;
	bool heldByPlayer;
	int teamID;
	int playerID;
	float _distanceTraveled;
	float _distanceGoal;
	Physics* _physics;
	bool _bigSnowball;
	bool _dead = false;
	
public:
	void setBigSnowBall(bool bigSB);
	Snowball(GameObject* player, float playerPower, float radians, std::string textureFileName);
	~Snowball();
	void OnStart() {};
	void OnUpdate(int ticks);
	void OnEnd() {};
	void DestructSnowball();
	void setHeld(bool held);
	void SetDistanceGoal(float dist);
};