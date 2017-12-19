#include "Transform.h"
#include "HelperFunctions.h"
#include "MessageManager.h"
#include "AI.h"
#include "NetworkingManager.h"
#include "SpriteRendererManager.h"
#include "PhysicsManager.h"
#include "MatchManager.h"
#include "UserDefinedRenderLayers.h"
#include "Battler.h"
#include "Snowball.h"
#include "GameManager.h"
#include "GameScene.h"
#include "SceneManager.h"

void ReceivedFireSnowball(std::map<std::string, void*> payload) {
	Battler* self = (Battler*)payload["this"];
	self->ThrowSnowball();
}

Battler::Battler(int team, std::string textureFileName, std::string networkingID, bool isSender) : ComplexSprite(GenerateSpriteInfo(team), 0.0f, 0.0f)
{
	this->networkingID = networkingID;
	this->isSender = isSender;
	if (!isSender) {
		MessageManager::Subscribe(networkingID + "|FIRE", ReceivedFireSnowball, this);
	}
	InitStats(team);
}

Battler::Battler(int team, std::string textureFileName) : ComplexSprite(GenerateSpriteInfo(team), 0.0f, 0.0f)
{
	this->isSender = false;
	this->networkingID = -1;
	InitStats(team);
	GetComponent<SpriteRenderer*>()->SetLayer(RENDER_LAYER_SHADOWABLE);
}

/*Battler::~Battler()
{

}*/

void Battler::OnUpdate(int ticks)
{
	if (_transform == NULL)
	{
		_transform = GetTransform();
	}

	float deltaTime = (float)ticks / 1000.0f;

	UpdateThrowTimer(deltaTime);
	UpdateAttachedSnowBalls(deltaTime);
	//if (!CheckIfInBounds(_transform->getX(), _transform->getY()))
	//{
	//	Move(0, 0);
	//}
}

void Battler::InitStats(int team)
{
	_physics = new Physics(this);
	AddComponent<Physics*>(_physics);
	stats.teamID = team;
	stats.moveSpeed = 2;
	stats.fireSpeedInterval = 1;
	stats.isPlayer = false;
	stats.hitpoints = 1;
	stats.isattached = false;
	_throwPower = 5;
	_throwDistance = 25;
}


bool Battler::Move(float x, float y)
{
	if (GetCurrentSprite() != SPRITE_SIMPLE_THROW) {
		if (x >= .5 || x <= -.5 || y >= .5 || x <= -.5) {
			ChangeSprite(SPRITE_WALK);
		} else {
			ChangeSprite(SPRITE_IDLE);
		}
	}
	if (!_fullLock && !_makingSnowball) {
		Transform *t = GetTransform();
		Vector2 *v = new Vector2(x, y);
		CheckIfInBounds(t, v);
		ApplyIceSliding(v);
		_physics->setVelocity(v);
		float snowdrag = _physics->getSnowDrag();
		float drag = _physics->getDrag();
		if (attachedSnowballs.size() > 3) {
			//Die();
		}
		else {
			if (_bigSnowball != NULL && attached) {
				Vector2 *v = new Vector2(x, y);
				Physics* physics = _bigSnowball->GetComponent<Physics*>();
				physics->setDrag(drag);
				physics->setSnowDrag(snowdrag);
				physics->setVelocity(v);
			}
			for (int i = 0; i < attachedSnowballs.size(); i++) {
				Vector2 *v = new Vector2(x, y);
				Physics* physics = attachedSnowballs[i]->GetComponent<Physics*>();
				physics->setDrag(drag);
				physics->setSnowDrag(snowdrag);
				physics->setVelocity(v);
			}
		}
        return true;
    }
    else {
		if (_bigSnowball != NULL && attached) {
			Vector2 *v = new Vector2(0,0);
			Physics* physics = _bigSnowball->GetComponent<Physics*>();
			physics->setVelocity(v);
		}
        _physics->setVelocity(new Vector2(0, 0));
		for (int i = 0; i < attachedSnowballs.size(); i++) {
			Vector2 *v = new Vector2(0, 0);
			Physics* physics = attachedSnowballs[i]->GetComponent<Physics*>();
			physics->setVelocity(v);
		}
    }

	return false;
}

Vector2 *Battler::GetVelocity() {
	return _physics->getVelocity();
}

void Battler::Face(GameObject* gameObject)
{
	
}

void Battler::Face(Vector2* position)
{

}

void Battler::TurnTo(GameObject* gameObject)
{

}

void Battler::TurnTo(Vector2* position)
{

}

bool Battler::ThrowSnowball()
{
	if (!canFire)
 		return false;

	ChangeSprite(SPRITE_SIMPLE_THROW, SPRITE_IDLE);

	if (isSender) {
		std::map<std::string, std::string> payload;
		NetworkingManager::GetInstance()->PrepareMessageForSending(networkingID + "|FIRE", payload);
	}

	float radians = GetComponent<Transform*>()->getRotation() * M_PI / 180;

	std::string snowballColour = "Snowball2.png";
	if (stats.teamID == 2)
		snowballColour = "Snowball3.png";

	Snowball* snowball = new Snowball(this, 5, radians, snowballColour);
	canFire = false;
	return true;
}

void Battler::UpdateThrowTimer(float deltaTime)
{
	timeSinceLastShot += deltaTime;
	if (timeSinceLastShot > stats.fireSpeedInterval)
	{
		canFire = true;
		timeSinceLastShot = 0.0f;
	}
}

void Battler::UpdateAttachedSnowBalls(float deltaTimer) {
	
}

bool Battler::DealtDamage(int damage)
{
	bool isattached = false;
	stats.hitpoints -= damage;
	_physics->setSnowDrag(_physics->getSnowDrag()* 0.7);
	if (stats.hitpoints <= 0)
	{
		Die();
		return true;
	}
	if (stats.isattached)
	{
		ThrowSnowball();

	}
	else
	{
	//	Snowball* snowball = new Snowball();
		
	//	GetGameObject()->GetTransform()->addTranslation()->Player position;
		
	}
	//return true;

	return false;
}

/*bool Battler::IsAttached()
{
	if (stats.isattached)
	{
		find.Player();
	}
	else
	{
		Snowball* snowball = new Snowball();
		GetGameObject() -> GetTransform()->addTranslation()->Player position;
	}
	return true;
}*/

void Battler::Die()
{
	GameObject* snowman = new GameObject(false);
	snowman->AddComponent<SpriteRenderer*>(new SpriteRenderer(snowman));
	SpriteRenderer* spriteRenderer = snowman->GetComponent<SpriteRenderer*>();
	GLuint textureTileSet = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/BackgroundTileSet.png"));
	spriteRenderer->SetActiveSprite((ISprite*)new SpriteSheet(textureTileSet, 8, 4, 0,static_cast<int>(TileIndex::Snow_Center_Alt4_Snowman)));
	spriteRenderer->SetActiveShader(Shader::GetShader(SHADER_SPRITESHEET));
	spriteRenderer->SetLayer(RENDER_LAYER_SHADOWABLE);
	snowman->GetTransform()->setPosition(GetTransform()->getX(), GetTransform()->getY(), GetTransform()->getZ());
	snowman->GetTransform()->setRotation(GetTransform()->getRotation());

	dynamic_cast<GameScene*>(SceneManager::GetInstance()->GetCurrentScene())->thingsToClear.push_back(snowman);

	if (stats.isPlayer)
	{
		int winningTeam = 1;
		if (stats.teamID == 1)
			winningTeam = 2;

		if (NetworkingManager::GetInstance()->IsConnected() && isSender) {
			std::map<std::string, std::string> payloadNet;
			payloadNet["teamID"] = std::to_string(winningTeam);
			NetworkingManager::GetInstance()->PrepareMessageForSending("PlayerWon", payloadNet);
		}

		std::map<std::string, void*> payload;
		payload["teamID"] = new std::string(std::to_string(winningTeam));
		MessageManager::SendEvent("PlayerWon", payload);
		
	}
	else if (HasComponent<AI*>()) {
		GetComponent<AI*>()->Died();
	}
	else {
		if (networkingID.find("Player") == string::npos) {
			stats.hitpoints = 1;
			return;
		}
		for (int i = 0; i < attachedSnowballs.size(); i++) {
			Destroy(attachedSnowballs[i]);
		}
		MatchManager::GetInstance()->UnRegisterCharacter(this);
	}
}

ComplexSpriteinfo* Battler::GenerateSpriteInfo(int team) {
	ComplexSpriteinfo* info = new ComplexSpriteinfo();
	if (team == 1) {
		info->AddInfo("Character_IdleSheet.png", 8, 1);
		info->AddInfo("Character_MoveSheet.png", 8, 1);
		info->AddInfo("Character_ThrowSheet.png", 8, 1);
	} else {
		info->AddInfo("Character2_IdleSheet.png", 8, 1);
		info->AddInfo("Character2_MoveSheet.png", 8, 1);
		info->AddInfo("Character2_ThrowSheet.png", 8, 1);
	}
	

	return info;
}

void Battler::LockToBattler(Snowball* sb) { 
	attachedSnowballs.push_back(sb);

}

void Battler::Unlock() {
	//
}


//------------------------------------------------------
//BIG SNOWBALL METHODS
//------------------------------------------------------

//should be called every update for each player/ai on screen
void Battler::HandleBigThrow(float deltaTime) {
	if (_bigSnowball == NULL) {
		return;
	}
	if (_fullLock && _timer < 2)
		_timer += deltaTime;
	else if (_fullLock && _timer > 2) {
		//launch snowball
		//Unlock();
		attached = false;
		_bigSnowball->setHeld(false);
		_bigSnowball->SetDistanceGoal(_throwDistance);
		float radians = GetComponent<Transform*>()->getRotation() * M_PI / 180;
		Vector2* velocity = new Vector2(1, 0);
		velocity = *velocity * _throwPower;
		velocity->rotateVector(radians);
		_bigSnowball->GetComponent<Physics*>()->setVelocity(velocity);
		_haveBigSnowball = false;
		_fullLock = false;
		_throwDistance = 25;
	}
}

//keep calling until return true
bool Battler::MakeBigSnowball(float deltaTime) {
	if (!_fullLock && !_haveBigSnowball) {
		if (_makingSnowball) {
			if (_timer < 2) {
				if(_bigSnowball != NULL && _bigSnowball->GetTransform() != NULL){
					_bigSnowball->GetTransform()->addScale(0.01f);
				}
				_timer += deltaTime;
				_animate = true;
			}
			else {
				//made snowball
				_makingSnowball = false;
				attached = true;
				//LockToBattler();
				_bigSnowball->setHeld(true);
				_animate = false;
				_physics->setDrag(0.4f);
				_haveBigSnowball = true;
				return true;
			}
		}
		else {
			//starting to make snowball
			std::string snowballColour = "Snowball2.png";
			if (stats.teamID == 2)
				snowballColour = "Snowball3.png";
			float radians = GetComponent<Transform*>()->getRotation() * M_PI / 180 / 2;
			_bigSnowball = new Snowball(this, 0, radians, snowballColour);
			_bigSnowball->setBigSnowBall(true);
			if(this->stats.teamID == 1)
				_bigSnowball->GetTransform()->addX(0.7f);
			else
				_bigSnowball->GetTransform()->addX(-0.7f);
			_bigSnowball->GetTransform()->setZ(-1);
			_timer = 0;
			_makingSnowball = true;
		}
	}
	return false;
}

bool Battler::FireBigSnowball() {
	if (_haveBigSnowball) {
		if (_fullLock) {
			_throwPower += 2.0f; //ai wont care about this
			return true;
		}
		else{
			_physics->setDrag(1);
			_timer = 0;
			_fullLock = true;
			return true;
		}
	}
	return false;
}

bool Battler::GetBigSnowball() {
	return _haveBigSnowball;
}

void Battler::AnimateCreation() {

}

void Battler::HandleCancels() {
	if (!_fullLock) {
		if (_timer < 2 && _makingSnowball) {
			//cancel snowball creation
			if(_bigSnowball != NULL){
				Destroy(_bigSnowball);
				_bigSnowball = NULL;
			}
			_makingSnowball = false;
			_timer = 0;
			_animate = false;
		}
	}
}

//-------------------------------------------------

bool Battler::CheckIfInBounds(Transform *pos, Vector2 *move)
{
	float xMin = (-getGameWidth() / 2) - 2;
	float xMax = (getGameWidth() / 2) + 2;
	float yMax = (getGameHeight() / 2) + 1.25;
	float yMin = -(getGameHeight() / 2) - 1;

	float team1Bounds = (xMin + ((xMax - xMin) / 2)) + 7;
	float team2Bounds = (xMin + ((xMax - xMin) / 2)) - 6;

	bool inBounds = true;

	unique_ptr<Vector2> newPos(new Vector2(pos->getX() + move->getX(), pos->getY() + move->getY()));

	if (newPos->getX() <= (stats.teamID == 2 ? team2Bounds : xMin)) {
		if (move->getX() < 0)
			move->setX(0);
		inBounds = false;
	}

	if (newPos->getX() >= (stats.teamID == 1 ? team1Bounds : xMax)) {
		if (move->getX() > 0)
			move->setX(0);
		inBounds = false;
	}

	if (newPos->getY() <= yMin) {
		if (move->getY() < 0)
			move->setY(0);
		inBounds = false;
	}

	if (newPos->getY() >= yMax) {
		if (move->getY() > 0)
			move->setY(0);
		inBounds = false;
	}
	return inBounds;
}

bool Battler::InIceZone(Transform *t) {
	float xMin = (-getGameWidth() / 2) - 2;
	float xMax = (getGameWidth() / 2) + 2;
	float yMax = (getGameHeight() / 2) - .75;
	float yMin = -(getGameHeight() / 2) + 1;

	float team1Bounds = (xMin + ((xMax - xMin) / 2)) + 5;
	float team2Bounds = (xMin + ((xMax - xMin) / 2)) - 4;

	return (t->getX() >= team2Bounds && t->getX() <= team1Bounds && t->getY() >= yMin && t->getY() <= yMax);
}

bool Battler::ApplyIceSliding(Vector2 *v) {
	if (InIceZone(GetTransform())) {
		std::cout << "X: " << v->getX() << " Y: " << v->getY();
		v->setX(v->getX() * 0.99f);
		v->setY(v->getY() * 0.99f);
		std::cout << "2X: " << v->getX() << " 2Y: " << v->getY() << std::endl;
		return true;
	}
	return false;
}
