#pragma once
#include <vector>
#include "Vector2.h"

using namespace std;

//struct Data {
//	vector<Vector2> friendlySnowballPos;
//	vector<Vector2> enemySnowballPos;
//	vector<Vector2> playerSnowballPos;
//	vector<Vector2> enemyBattlerPos;
//	vector<Vector2> friendlyAIPos;
//	Vector2 friendlyPlayerPos;
//	double myTeam;
//
//	double threwSnowball;
//	double movedLeft;
//	double movedRight;
//	double movedUp;
//	double movedDown;
//};

struct Data {
	
	Data(){}
	Vector2 friendlyPlayerPos = Vector2(0.0, 0.0);
	Vector2 friendlyPlayerVelocity = Vector2(0.0, 0.0);

	double threwSnowball;
	double velocityX;
	double velocityY;
};

class TrainingData
{
public:
	TrainingData();
	~TrainingData();

	void GetTopology(vector<unsigned> &topology);
	unsigned GetNextInputs(vector<double> &inputValues, Data &gameState);
	unsigned GetTargetOutputs(vector<double> &targetOutputValues, Data &gameState);

	vector<Data> savedData;

private:
	int GetInputNeuronCount();
	Vector2 NormalizeVector2(Vector2 &position);

};

