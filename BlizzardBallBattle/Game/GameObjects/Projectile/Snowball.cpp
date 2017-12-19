#include "Snowball.h"
#include "Physics.h"
#include "SharedConstants.h"
#include "SpriteRendererManager.h"
#include "PhysicsManager.h"
#include "Collision/Collider.h"
#include "UserDefinedRenderLayers.h"
#include "MessageManager.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "GameScene.h"
#include <stdlib.h>
#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS


Snowball::Snowball(GameObject* player, float playerPower, float radians, std::string textureFileName) : SimpleSprite(textureFileName, 0.0f, 0.0f),_player(player) {
	_physics = new Physics(this);
	AddComponent<Physics*>(_physics);
	GetTransform()->setX(_player->GetTransform()->getX());
	GetTransform()->setY(_player->GetTransform()->getY());
	GetTransform()->setScale(0.5f);
	teamID = dynamic_cast<Battler*>(_player)->stats.teamID;
	playerID = dynamic_cast<Battler*>(_player)->getId();

	//AddComponent<Collider*>(new Collider(this, 50.0f));
	AddComponent<Collider*>(new Collider(this, GetTransform()->getScale() / 2));
	myCollider = GetComponent<Collider*>();

	_speed = playerPower;
	Vector2* velocity = new Vector2(1, 0);

	velocity = *velocity * _speed;
	velocity->rotateVector(radians);
	_physics->setVelocity(velocity);
	active = true;
	GetComponent<SpriteRenderer*>()->SetLayer(RENDER_LAYER_SHADOWABLE);
	heldByPlayer = false;
	_bigSnowball = false;
	//dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene())->thingsToClear.push_back(this);
}

void Snowball::OnUpdate(int timeDelta)
{
	if (_dead) {
		return;
	}
	std::cout << "SNOWBALL::START" << std::endl;

	//If the scene is not a GameScene, destroy self
	if (!dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene())) {
		Destroy(this);
	}
	//if (heldByPlayer) {
	//	if (dynamic_cast<Battler*>(_player)->stats.teamID == 1) {
	//		GetTransform()->setX(_player->GetTransform()->getX() + 0.7f);
	//		GetTransform()->setY(_player->GetTransform()->getY());
	//	}
	//	else {
	//		GetTransform()->setX(_player->GetTransform()->getX() - 0.7f);
	//		GetTransform()->setY(_player->GetTransform()->getY());
	//_distanceTraveled += _physics->getVelocity()->getX() * timeDelta;
	//	}
	//}


	if (active) {
		std::cout << "SNOWBALL::START::ACTIVE" << std::endl;
		if (_distanceGoal != 0 && _distanceTraveled >= _distanceGoal) {
			DestructSnowball();
			return;
		}
		if(!heldByPlayer)
			GetTransform()->addRotation(15);

		if (myCollider->collisionDetected())
		{
			std::vector<GameObject*> v = myCollider->getColliders();
			char path[200];
			sprintf(path, "Game/Assets/Audio/hit%d.mp3", (rand() % 3));
			AudioManager::GetInstance()->PlaySEFhit(BuildPath(path), 1, 10);
			for (int i = 0; i < v.size(); i++) {
				if (v[i] == NULL || v[i] == nullptr || v[i]->GetTransform() == NULL || v[i]->GetTransform() == nullptr) {
					continue;
				}
				Battler *hitBattler = dynamic_cast<Battler*>(v[i]);
				if (hitBattler && (v[i]->getId() != playerID)) {
					//yes we hit do stuff
					if (hitBattler->stats.teamID != teamID) {
						int damage = 0;
						if (_bigSnowball) {
							damage = 10;
						}
						else {
							damage = 1;
						}
						if (hitBattler->DealtDamage(damage)) {
							std::cout << "SNOWBALL::KILLBATTLER" << std::endl;
							Destroy(v[i]);
							DestructSnowball();
							return;
						}
						else {
							hitBattler->LockToBattler(this);
							_physics->setVelocity(new Vector2(0, 0));
							active = false;
						}
					}
				}
			}
		}

		float x = GetTransform()->getX();
		if (x < -GAME_WIDTH / 2 || x > GAME_WIDTH / 2) {
			DestructSnowball();
		}
		std::cout << "SNOWBALL::END::ACTIVE" << std::endl;
	}

	std::cout << "SNOWBALL::END" << std::endl;
}

void Snowball::DestructSnowball() {
	std::cout << "SNOWBALL::DESTRUCTSNOWBALL" << std::endl;
	Destroy(this); //TODO: Fix with Snowball Destruction
	_dead = true;
}

void Snowball::setHeld(bool held) {
	heldByPlayer = held;
}

void Snowball::setBigSnowBall(bool bigSB) {
	_bigSnowball = bigSB;
}
	
void Snowball::SetDistanceGoal(float dist) {
	_distanceGoal = dist;
}

Snowball::~Snowball() {
	_dead = true;
}
