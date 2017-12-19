#include "MenuScene_Alpha.h"
#include "SpriteRendererManager.h"
#include "HelperFunctions.h"
#include "SharedConstants.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "GameManager.h"

void MenuScene_Alpha::OnEnd() {
    DestroyBaseScene();
}

void MenuScene_Alpha::BuildBaseScene() {
	Camera::SetActiveCamera(new Camera());
    menuBackground = new SimpleSprite("Sky.png", 0.0f, 0.0f, -2, GAME_WIDTH, Shader::GetShader(SHADER_PIXEL));
    menuForeground = new SimpleSprite("ForegroundTrees.png", 0.0f, -getGameHeight()/5.0f, -1, GAME_WIDTH, Shader::GetShader(SHADER_PIXEL));
}

void MenuScene_Alpha::DestroyBaseScene() {
	GameManager::GetInstance()->RemoveGameObject(menuBackground);
	GameManager::GetInstance()->RemoveGameObject(menuForeground);
}