#pragma once

#ifndef MATCH_MANAGER_H
#define MATCH_MANAGER_H
#include <iostream>
#include "GameObject.h"
#include "Battler.h"
#include "AI.h"
#include <vector>
#include "AILearning.h"

class MatchManager
{
private:
	//Singleton variables
	static MatchManager *instance;
	std::vector<Battler*> teamOne;
	std::vector<Battler*> teamTwo;
	Battler* playerOne;
	Battler* playerTwo;
	std::vector<AI*> teamOneAIUnits;
	std::vector<AI*> teamTwoAIUnits;
	int TEAM_SIZE;
public:
	static MatchManager* GetInstance();
	MatchManager();
	~MatchManager();
	void StartGame();
	bool RegisterCharacter(Battler *character);
	bool UnRegisterCharacter(Battler *character);
	void CreateBattlers(Shader *shader, GLuint characterTexture, GLuint spriteSheetTexture, int teamOneFormation, int teamTwoFormation);
	std::vector<Battler*> GetTeam(int teamID);
	void Stop();
	AILearning teamOneNet;
	AILearning teamTwoNet;
};
#endif