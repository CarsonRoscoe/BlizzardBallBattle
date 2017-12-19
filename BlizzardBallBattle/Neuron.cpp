#include "Neuron.h"
#include <cstdlib>
#include <cmath>

double Neuron::learningRate = 0.15;
double Neuron::alpha = 0.5;

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
	m_myIndex = myIndex;

	for (unsigned connections = 0; connections < numOutputs; ++connections)
	{
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = RandomWeight();
	}
}


Neuron::~Neuron()
{
}

double Neuron::RandomWeight(void)
{
	return rand() / double(RAND_MAX);
} 

void Neuron::FeedForward(const Layer &previousLayer)
{
	double sum = 0.0;

	// Sum the previous layer's outputs (which are our inputs)
	// Include the bias node from the previous layer.
	for (unsigned n = 0; n < previousLayer.size(); ++n)
	{
		sum += previousLayer[n].GetOutputValue() *
			previousLayer[n].m_outputWeights[m_myIndex].weight;
	}

	m_outputVal = Neuron::TransferFunction(sum);
}

double Neuron::TransferFunction(double x)
{
	// Tanh - output range {-1.0...1.0}
	return tanh(x);
}

double Neuron::TransferFunctionDerivative(double x)
{
	// Tanh derivative
	return 1.0 - x * x;
}

void Neuron::CalculateOutputGradients(double targetVal)
{
	double delta = targetVal - m_outputVal;
	m_gradient = delta * Neuron::TransferFunctionDerivative(m_outputVal);
}

void Neuron::CalculateHiddenGradients(const Layer &nextLayer)
{
	double dow = SumDOW(nextLayer);
	m_gradient = dow * Neuron::TransferFunctionDerivative(m_outputVal);
}

double Neuron::SumDOW(const Layer &nextLayer) const
{
	double sum = 0.0;

	// Sum out contributions of the errors at the nodes we feed
	for (unsigned n = 0; n < nextLayer.size() - 1; ++n)
	{
		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}

	return sum;
}

void Neuron::UpdateInputWeights(Layer &prevLayer)
{
	for (unsigned n = 0; n < prevLayer.size(); ++n)
	{
		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

		double newDeltaWeight =
			// Individual input, magnified by the gradient and training rate
			Neuron::learningRate * neuron.GetOutputValue() * m_gradient
			// Also add momentum = a fraction of the previous delta weight
			+ Neuron::alpha * oldDeltaWeight;

		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
	}
}
