#pragma once
#include <vector>
#include "Neuron.h"

using namespace std;

typedef vector<Neuron> Layer;

class NeuralNet
{
public:
	NeuralNet();
	~NeuralNet();
	void FeedForward(const vector<double> &inputVals);
	void BackProp(const vector<double> &targetVals);
	void GetResults(vector<double> &resultVals) const;
	double GetRecentAverageError(void) const { return m_recentAverageError; };
	void Initialize(const vector<unsigned> &topology);

private: 
	vector<Layer> m_layers;
	double m_error;
	double m_recentAverageError;
	double m_recentAverageSmoothingFactor;
};

