#pragma once
#include <vector>

using namespace std;

class Neuron;
typedef vector<Neuron> Layer;

struct Connection
{
	double weight;
	double deltaWeight;
};

class Neuron
{
public:
	Neuron(unsigned numOutputs, unsigned myIndex);
	~Neuron();
	void SetOutputValue(double val) { m_outputVal = val; }
	double GetOutputValue() const { return m_outputVal; }
	void FeedForward(const Layer &prevLayer);
	void CalculateOutputGradients(double targetVal);
	void CalculateHiddenGradients(const Layer &nextLayer);
	void UpdateInputWeights(Layer &prevLayer);

private:
	double m_outputVal;
	vector<Connection> m_outputWeights;
	static double RandomWeight(void);
	unsigned m_myIndex;
	static double TransferFunction(double x);
	static double TransferFunctionDerivative(double x);
	double SumDOW(const Layer &nextLayer) const;

	double m_gradient;
	static double learningRate; // Goes from 0 (no learning) to 1 (reckless)
	static double alpha; // Goes from 0 to n (multiplier of last weight change - momentum)
};