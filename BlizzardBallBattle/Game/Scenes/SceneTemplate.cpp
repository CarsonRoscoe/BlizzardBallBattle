#include "SceneTemplate.h"
#include "MatchManager.h"
#include "GLHeaders.h"
#include "SpriteRendererManager.h"
#include "Shader.h"
#include "SharedConstants.h"
#include "Sender.h"
#include "Receiver.h"
#include "SpriteSheet.h"
#include <iostream>

SceneTemplate::SceneTemplate(int p1ai, int p2ai) : GameScene(p1ai, p2ai) {
	this->p1ai = p1ai;
	this->p2ai = p2ai;
}

void SceneTemplate::OnStart(){
	BuildBaseScene();
	GLuint snowTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/SnowTile.png"));
	GLuint iceTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/IceTile.png"));
	GLuint characterTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/Character.png"));
	GLuint spriteSheetTexture = SpriteRendererManager::GetInstance()->GenerateTexture(BuildPath("Game/Assets/Sprites/WalkingSpriteSheet.png"));

	// Create Players
	MatchManager::GetInstance()->CreateBattlers(Shader::GetShader(), characterTexture, spriteSheetTexture, p1ai, p2ai);
}

void SceneTemplate::OnPause() {
	MatchManager::GetInstance()->Stop();
	ClearScene();
}

void SceneTemplate::OnEnd() {
}

void SceneTemplate::OnUpdate(int ticks) {
	//player1->GetComponent<Sender*>()->SendUpdate();
	//NetworkingManagerTemp::GetInstance()->SendQueuedEvents();
}