#include "TrainingData.h"
#include <vector>
#include "HelperFunctions.h"

TrainingData::TrainingData()
{
}


TrainingData::~TrainingData()
{
}

// The topology is the size of each layer in our Neural Net.
// First layer is our input layer, then our compute layer, then our output layer.
void TrainingData::GetTopology(vector<unsigned> &topology)
{
	unsigned inputNeurons = GetInputNeuronCount();
	topology.push_back(inputNeurons);

	unsigned outputNeurons = 3; // All our different types of target data;
	unsigned hiddenNeurons = (inputNeurons + outputNeurons) / 2; // The average of the two

	topology.push_back(hiddenNeurons);
	topology.push_back(outputNeurons);
}

// This will get the data being inputted into our Neural Net.
unsigned TrainingData::GetNextInputs(vector<double> &inputValues, Data &gameState)
{
	inputValues.clear();

	Vector2 normalizedPos = NormalizeVector2(gameState.friendlyPlayerPos);
	inputValues.push_back(normalizedPos.getX());
	inputValues.push_back(normalizedPos.getY());

	Vector2 normalizedPos2 = NormalizeVector2(gameState.friendlyPlayerVelocity);
	inputValues.push_back(normalizedPos2.getX());
	inputValues.push_back(normalizedPos2.getY());

	return inputValues.size();
}

// This is for training our data. It tells our Neural Net what it should have
// predicted as output given our input.
unsigned TrainingData::GetTargetOutputs(vector<double> &targetOutputValues, Data &gameState)
{
	targetOutputValues.clear();

	targetOutputValues.push_back(gameState.threwSnowball);
	targetOutputValues.push_back(gameState.velocityX);
	targetOutputValues.push_back(gameState.velocityY);

	return targetOutputValues.size();
}

int TrainingData::GetInputNeuronCount()
{
	int totalInputNeurons = 0;

	// One more for our player position
	totalInputNeurons += 2;

	// One more for the player velocity
	totalInputNeurons += 2;

	return totalInputNeurons;
}

//// This will get the data being inputted into our Neural Net.
//unsigned TrainingData::GetNextInputs(vector<double> &inputValues, Data &gameState)
//{
//	inputValues.clear();
//
//	for (int i = 0; i < gameState.friendlySnowballPos.size(); ++i)
//	{
//		Vector2 normalizedPos = NormalizeVector2(gameState.friendlySnowballPos[i]);
//		inputValues.push_back(normalizedPos.getX());
//		inputValues.push_back(normalizedPos.getY());
//	}
//
//	for (int i = 0; i < gameState.enemySnowballPos.size(); ++i)
//	{
//		Vector2 normalizedPos = NormalizeVector2(gameState.enemySnowballPos[i]);
//		inputValues.push_back(normalizedPos.getX());
//		inputValues.push_back(normalizedPos.getY());
//	}
//
//	for (int i = 0; i < gameState.playerSnowballPos.size(); ++i)
//	{
//		Vector2 normalizedPos = NormalizeVector2(gameState.playerSnowballPos[i]);
//		inputValues.push_back(normalizedPos.getX());
//		inputValues.push_back(normalizedPos.getY());
//	}
//
//	for (int i = 0; i < gameState.enemyBattlerPos.size(); ++i)
//	{
//		Vector2 normalizedPos = NormalizeVector2(gameState.enemyBattlerPos[i]);
//		inputValues.push_back(normalizedPos.getX());
//		inputValues.push_back(normalizedPos.getY());
//	}
//
//	for (int i = 0; i < gameState.friendlyAIPos.size(); ++i)
//	{
//		Vector2 normalizedPos = NormalizeVector2(gameState.friendlyAIPos[i]);
//		inputValues.push_back(normalizedPos.getX());
//		inputValues.push_back(normalizedPos.getY());
//	}
//
//	Vector2 normalizedPos = NormalizeVector2(gameState.friendlyPlayerPos);
//	inputValues.push_back(normalizedPos.getX());
//	inputValues.push_back(normalizedPos.getY());
//
//	inputValues.push_back(gameState.myTeam);
//
//	return inputValues.size();
//}
//
//// This is for training our data. It tells our Neural Net what it should have
//// predicted as output given our input.
//unsigned TrainingData::GetTargetOutputs(vector<double> &targetOutputValues, Data &gameState)
//{
//	targetOutputValues.clear();
//
//	targetOutputValues.push_back(gameState.threwSnowball);
//	targetOutputValues.push_back(gameState.movedLeft);
//	targetOutputValues.push_back(gameState.movedRight);
//	targetOutputValues.push_back(gameState.movedUp);
//	targetOutputValues.push_back(gameState.movedDown);
//
//	return targetOutputValues.size();
//}
//
//int TrainingData::GetInputNeuronCount(Data gameState)
//{
//	int totalInputNeurons = 0;
//
//	totalInputNeurons += gameState.enemyBattlerPos.size() * 2;
//	totalInputNeurons += gameState.friendlyAIPos.size() * 2;
//	totalInputNeurons += gameState.friendlySnowballPos.size() * 2;
//	totalInputNeurons += gameState.enemySnowballPos.size() * 2;
//	totalInputNeurons += gameState.playerSnowballPos.size() * 2;
//
//	// One more for our player position
//	totalInputNeurons += 2;
//
//	// One more for the team ID
//	totalInputNeurons += 1;
//
//	return totalInputNeurons;
//}

Vector2 TrainingData::NormalizeVector2(Vector2 &position)
{
	Vector2 normalizedData = Vector2(position.getX(), position.getY());

	return normalizedData;
}
