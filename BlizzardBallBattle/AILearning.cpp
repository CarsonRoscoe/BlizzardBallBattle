#include "AILearning.h"
#include "MatchManager.h"
#include "Physics.h"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

AILearning::AILearning()
{
	Initialize();
} 


AILearning::~AILearning()
{
}

void AILearning::Initialize()
{
	trainingData = TrainingData();

	vector<unsigned> topology;
	trainingData.GetTopology(topology);
	myNet = NeuralNet();
	myNet.Initialize(topology);
}

vector<double> AILearning::MakeDecision(Battler *player)
{
	Data newWorldData = Data();
	vector<double> inputValues, resultValues;
	vector<unsigned> topology;
	trainingData.GetTopology(topology);

	newWorldData.friendlyPlayerPos = Vector2(player->GetTransform()->getX(), player->GetTransform()->getY());
	newWorldData.friendlyPlayerVelocity = Vector2(player->GetComponent<Physics*>()->getVelocity()->getX(), player->GetComponent<Physics*>()->getVelocity()->getY());

	// Get new input data and feed it forward
	trainingData.GetNextInputs(inputValues, newWorldData);
	myNet.FeedForward(inputValues);

	myNet.GetResults(resultValues);
	return resultValues;
}

void AILearning::TrainData(Battler *player, double didShoot)
{
	Data newPlayerData = Data();
	vector<double> inputValues, resultValues, targetValues;
	vector<unsigned> topology;
	trainingData.GetTopology(topology);

	double velocityX = player->GetComponent<Physics*>()->getVelocity()->getX();
	double velocityY = player->GetComponent<Physics*>()->getVelocity()->getY();

	newPlayerData.friendlyPlayerPos = Vector2(player->GetTransform()->getX(), player->GetTransform()->getY());
	newPlayerData.friendlyPlayerVelocity = Vector2(velocityX, velocityY);

	newPlayerData.threwSnowball = didShoot;
	newPlayerData.velocityX = velocityX;
	newPlayerData.velocityY = velocityY;

	// Get new input data and feed it forward
	if (trainingData.GetNextInputs(inputValues, newPlayerData) != topology[0])
	{
		return;
	}
	myNet.FeedForward(inputValues);

	myNet.GetResults(resultValues);

	// Train the Neural Net what the outputs should have been
	trainingData.GetTargetOutputs(targetValues, newPlayerData);
	assert(targetValues.size() == topology.back());

	myNet.BackProp(targetValues);
}


vector<Vector2> GetPositions(vector<Battler*> gameObjects)
{
	vector<Vector2> positions;

	for (int i = 0; i < gameObjects.size(); ++i)
	{
		Vector2 position = Vector2(gameObjects[i]->GetTransform()->getX(), gameObjects[i]->GetTransform()->getY());
		positions.push_back(position);
	}

	return positions;
}


//void AILearning::Initiate()
//{
//	trainingData = TrainingData();
//
//	vector<unsigned> topology;
//	trainingData.GetTopology(topology, trainingData.savedData[0]);
//	NeuralNet myNet = NeuralNet(topology);
//
//	vector<double> inputValues, targetValues, resultValues;
//
//	for (unsigned i = 0; i < trainingData.savedData.size(); ++i)
//	{
//		// Get new input data and feed it forward
//		if (trainingData.GetNextInputs(inputValues, trainingData.savedData[i]) != topology[0])
//		{
//			return;
//		}
//		PrintVectorValues("Inputs: ", inputValues);
//		myNet.FeedForward(inputValues);
//
//		// Get the Neural Net's acrual results
//		myNet.GetResults(resultValues);
//		PrintVectorValues("Outputs: ", resultValues);
//
//		// Train the Neural Net what the outputs should have been
//		trainingData.GetTargetOutputs(targetValues, trainingData.savedData[i]);
//		PrintVectorValues("Targets: ", targetValues);
//		assert(targetValues.size() == topology.back());
//
//		myNet.BackProp(targetValues);
//
//		cout << "Neural Net recent average error: "
//			<< myNet.GetRecentAverageError() << endl;
//	}
//}
//
//void AILearning::CaptureWorldData()
//{
//	Data newWorldData = Data();
//
//	newWorldData.enemyBattlerPos = GetPositions(MatchManager::GetInstance()->GetTeam(1));
//}
//
//vector<Vector2> GetPositions(vector<Battler*> gameObjects)
//{
//	vector<Vector2> positions;
//
//	for (int i = 0; i < gameObjects.size(); ++i)
//	{
//		Vector2 position = Vector2(gameObjects[i]->GetTransform()->getX(), gameObjects[i]->GetTransform()->getY());
//		positions.push_back(position);
//	}
//}
//
//void AILearning::PrintVectorValues(string initialLine, const vector<double> &vectorToPrint)
//{
//	cout << initialLine << " ";
//
//	for (int e = 0; e < vectorToPrint.size(); ++e)
//	{
//		cout << vectorToPrint[e] << " ";
//	}
//
//	cout << endl;
//}
