#pragma once
#include "NeuralNet.h"
#include "TrainingData.h"
#include "Battler.h"

class AILearning
{
public:
	AILearning();
	~AILearning();
	vector<double> MakeDecision(Battler *player);
	void TrainData(Battler *player, double didShoot);

private:
	//void PrintVectorValues(string initialLine, const vector<double> &vectorToPrint);
	void Initialize();
	TrainingData trainingData;
	NeuralNet myNet;
};

