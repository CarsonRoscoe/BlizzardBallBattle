#pragma once

#include "Scene.h"
#include "SimpleSprite.h"
#include "Shader.h"
#include <vector>

enum class TileIndex {
	//1st Row
	DirtHouseLeft_TopLeft,
	DirtHouseLeft_Top,
	DirtSnow_Top,
	DirtSnowIce_TopLeft,
	DirtSnowIce_Top,
	DirtSnowIce_TopRight,
	DirtHouseRight_Top,
	DirtHouseRight_TopRight,
	//2nd Row
	HouseLeft_Left,
	HouseLeft_Center,
	Snow_Center,
	SnowIce_Left,
	Ice_Center,
	SnowIce_Right,
	HouseRight_Center,
	HouseRight_Right,
	//3rd Row
	DirtHouseLeft_BottomLeft,
	DirtHouseLeft_Bottom,
	DirtSnow_Bottom,
	DirtSnowIce_BottomLeft,
	DirtSnowIce_Bottom,
	DirtSnowIce_BottomRight,
	DirtHouseRight_Bottom,
	DirtHouseRight_BottomRight,
	//4th Row
	HouseLeft_Center_Alt,
	Snow_Center_Alt1_Shrub,
	Snow_Center_Alt2_Shrub,
	Snow_Center_Alt3_Shrub,
	Snow_Center_Alt4_Snowman,
	Dirt_Center,
	Snow_Center_Alt6,
	HouseRight_Center_Alt
};

class GameScene : public Scene {
private:
	Shader* ourShader;
public:
	GameScene(int player1Choice, int player2Choice);
    void BuildBaseScene();
	void ClearScene();
	std::vector<GameObject*> thingsToClear;
};