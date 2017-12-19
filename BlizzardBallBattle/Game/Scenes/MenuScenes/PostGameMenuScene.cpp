#include "PostGameMenuScene.h"
#include "HelperFunctions.h"
#include "InputManager.h"
#include "GLHeaders.h"
#include "Scenes.h"
#include "SceneManager.h"
#include "Transform.h"

PostGameMenuScene::PostGameMenuScene(int winningTeamID) {
    if (winningTeamID == 1) {
        winnerTextPath = "TeamOneWon.png";
    } else if (winningTeamID == 2) {
        winnerTextPath = "TeamTwoWon.png";
    } else {
        //ERROR
    }
}

void PostGameMenuScene::OnStart() {
    BuildBaseScene();
    winnerText = new SimpleSprite(winnerTextPath, 0.0f, getGameTopY() - getGameHeight()/3.0f, 0.0f, GAME_WIDTH, Shader::GetShader(SHADER_PIXEL));
    spaceToReturnText = new SimpleSprite("ReturnToMenu.png", 0.0f, -getGameHeight() / 6.0f, 1.0f, GAME_WIDTH / 1.5f, Shader::GetShader(SHADER_PIXEL));
}

void PostGameMenuScene::OnPause() {
	DestroyBaseScene();
	winnerText->GetTransform()->setScale(0.0f);
	spaceToReturnText->GetTransform()->setScale(0.0f);
}

PostGameMenuScene::~PostGameMenuScene() {
    //delete(winnerText);
    //delete(spaceToReturnText);
}


void PostGameMenuScene::OnUpdate(int ticks) {
    InputManager* inputManager = InputManager::GetInstance();
    if (inputManager->onKeyPressed(SDLK_SPACE)) {
		SceneManager::GetInstance()->PushScene(new LaunchMenuScene());
    }
}