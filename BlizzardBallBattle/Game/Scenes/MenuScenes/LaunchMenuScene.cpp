#include "LaunchMenuScene.h"
#include "HelperFunctions.h"
#include "InputManager.h"
#include "GLHeaders.h"
#include "SceneManager.h"
#include "Scenes.h"
#include "NetworkingManager.h"
#include "Transform.h"
#include "GameManager.h"
#include "AudioManager.h"
#include "HelperFunctions.h"
//#include "TestGO.h"

void LaunchMenuScene::OnStart() { CreateScene(); }
void LaunchMenuScene::OnResume() { CreateScene(); }

void LaunchMenuScene::OnPause() { DestroyScene(); }
void LaunchMenuScene::OnEnd() { DestroyScene(); }

void LaunchMenuScene::CreateScene() {
    BuildBaseScene();
    menuTitle = new SimpleSprite("Title.png", 0.0f, getGameTopY() - getGameHeight()/3.0f, 0.0f, GAME_WIDTH, Shader::GetShader(SHADER_PIXEL));
    howToText = new SimpleSprite("HowTo.png", 0.0f, -getGameHeight() / 6.0f, 1.0f, GAME_WIDTH / 1.5f, Shader::GetShader(SHADER_PIXEL));
	AudioManager::GetInstance()->PlayMusic(BuildPath("Game/Assets/Audio/mario_.wav"), 1, 10);
}

void LaunchMenuScene::DestroyScene() {
	DestroyBaseScene();
	GameManager::GetInstance()->RemoveGameObject(menuTitle);
	GameManager::GetInstance()->RemoveGameObject(howToText);
}

void LaunchMenuScene::OnUpdate(int ticks) {
    InputManager* inputManager = InputManager::GetInstance();

    if (inputManager->onKeyPressed(SDLK_h)) {
        NetworkingManager::GetInstance()->CreateHost();
        SceneManager::GetInstance()->PushScene(new GameScene_Alpha_Networked());
    } else if (inputManager->onKeyPressed(SDLK_j)) {
        NetworkingManager::GetInstance()->CreateClient();
        SceneManager::GetInstance()->PushScene(new GameScene_Alpha_Networked());
    } else if (inputManager->onKeyPressed(SDLK_1)) {
		SceneManager::GetInstance()->PushScene(new PostGameMenuScene(1));
    } else if (inputManager->onKeyPressed(SDLK_2)) {
		SceneManager::GetInstance()->PushScene(new AISelectionMenuScene());
    }
}

