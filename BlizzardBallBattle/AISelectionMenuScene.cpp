#include "AISelectionMenuScene.h"
#include "HelperFunctions.h"
#include "InputManager.h"
#include "GLHeaders.h"
#include "Scenes.h"
#include "SceneManager.h"
#include "Transform.h"
#include "GameManager.h"

AISelectionMenuScene::AISelectionMenuScene() {}

void AISelectionMenuScene::OnStart() {
	BuildBaseScene();

	title = new SimpleSprite("AIScene_Title.png", 0.0f, getGameTopY() - getGameHeight() / 7.0f, 0.0f, GAME_WIDTH * 0.5f, Shader::GetShader(SHADER_PIXEL));
	ai1Preview = new SimpleSprite("AIScene_Preview1.png", getGameLeftX() + getGameWidth() / 5.0f, getGameTopY() - getGameHeight() / 2.5f, 0.0f, GAME_WIDTH * 0.2f, Shader::GetShader(SHADER_PIXEL));
	ai2Preview = new SimpleSprite("AIScene_Preview2.png", getGameLeftX() + getGameWidth() / 2.0f, getGameTopY() - getGameHeight() / 2.5f, 0.0f, GAME_WIDTH * 0.2f, Shader::GetShader(SHADER_PIXEL));
	ai3Preview = new SimpleSprite("AIScene_Preview3.png", getGameRightX() - getGameWidth() / 5.0f, getGameTopY() - getGameHeight() / 2.5f, 0.0f, GAME_WIDTH * 0.2f, Shader::GetShader(SHADER_PIXEL));
	oneStatus = new SimpleSprite("AIScene_PlayerOneUnchecked.png", getGameLeftX() + getGameWidth() / 4.0f, getGameBottomY() + getGameHeight() / 5.0f, 0.0f, GAME_WIDTH * 0.4f, Shader::GetShader(SHADER_PIXEL));
	twoStatus = new SimpleSprite("AIScene_PlayerTwoUnchecked.png", getGameRightX() - getGameWidth() / 4.0f, getGameBottomY() + getGameHeight() / 5.0f, 0.0f, GAME_WIDTH * 0.4f, Shader::GetShader(SHADER_PIXEL));

	p1Done = false;
	p2Done = false;
}

void AISelectionMenuScene::OnPause() {
	DestroyBaseScene();
	GameManager::GetInstance()->RemoveGameObject(title);
	GameManager::GetInstance()->RemoveGameObject(ai1Preview);
	GameManager::GetInstance()->RemoveGameObject(ai2Preview);
	GameManager::GetInstance()->RemoveGameObject(ai3Preview);
	GameManager::GetInstance()->RemoveGameObject(oneStatus);
	GameManager::GetInstance()->RemoveGameObject(twoStatus);
}

AISelectionMenuScene::~AISelectionMenuScene() {
	//delete(winnerText);
	//delete(spaceToReturnText);
}


void AISelectionMenuScene::OnUpdate(int ticks) {
	InputManager* inputManager = InputManager::GetInstance();
	if (inputManager->onKeyPressed(SDLK_a) && !p1Done) {
		p1Result = 1;
		p1Done = true;
		TryEnd();
	}
	if (inputManager->onKeyPressed(SDLK_s) && !p1Done) {
		p1Result = 2;
		p1Done = true;
		TryEnd();
	}
	if (inputManager->onKeyPressed(SDLK_d) && !p1Done) {
		p1Result = 3;
		p1Done = true;
		TryEnd();
	}

	if (inputManager->onKeyPressed(SDLK_j) && !p2Done) {
		p2Result = 1;
		p2Done = true;
		TryEnd();
	}
	if (inputManager->onKeyPressed(SDLK_k) && !p2Done) {
		p2Result = 2;
		p2Done = true;
		TryEnd();
	}

	if (inputManager->onKeyPressed(SDLK_l) && !p2Done) {
		p2Result = 3;
		p2Done = true;
		TryEnd();
	}
}


bool AISelectionMenuScene::TryEnd() {
	if (p1Done && p2Done) {
		SceneManager::GetInstance()->PushScene(new SceneTemplate(p1Result, p2Result));
	}

	return false;
}