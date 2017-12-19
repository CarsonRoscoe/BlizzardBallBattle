#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Battler.h"
#include "Transform.h"

class AI :
	public Component
{
private:
	Battler *myBattler;
	Transform *myTransform;

	enum Target {
		battler = 0,
		position = 1,
		t_MAX
	}currentTarget;
	GameObject *targetBattler;
	Vector2 *targetPosition;
	void GetTarget();
	GameObject* GetTargetBattler();
	Vector2* GetTargetPosition();

	enum State {
		idle = 0,
		walk = 1,
		shoot = 2,
		dead = 3,
		s_MAX
	}currentState;
	void WalkToTargetBattler();
	void WalkToTargetPosition();
	void SetLearnedVelocity();
	void Shoot();

	enum Behaviour {
		none = 0,
		cower = 1,
		engage = 2,
		b_MAX
	}currentBehaviour;
	void GetBehaviour();
	bool CanMakeDecision(float deltaTIme);

	float decisionFrequency;
	float timeSinceLastDecision;
	bool lastActionWasShooting;

	float intelligence;
	float courage;

	bool isLearning;
	int teamID;

public:
	AI(GameObject* gameObject, bool _isLearning);
	~AI();
	void Initialize(float _intelligence, float _courage, float _decisionFrequency);
	void Died();
	void OnStart(){};
	void OnUpdate(int ticks);
	void OnEnd(){};
	void Retarget();
};

