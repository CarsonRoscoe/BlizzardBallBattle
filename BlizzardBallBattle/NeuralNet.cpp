#include "NeuralNet.h"
// #include "Neuron.h"
#include <cassert>

NeuralNet::NeuralNet()
{

}

NeuralNet::~NeuralNet()
{
}

void NeuralNet::Initialize(const vector<unsigned> &topology)
{
	unsigned numLayers = topology.size();
	for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum)
	{
		m_layers.push_back(Layer());

		// The number of outputs is the number of Neurons in the next layer.
		// If this is the output layer (the last layer in our net), then the output Neruons are 0.
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];
		// Created a new layer, now let's fill it with Neurons!
		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
		{
			m_layers.back().push_back(Neuron(numOutputs, neuronNum));
		}

		// Force the bias node's output value to 1.0. It's the last neuron created above
		m_layers.back().back().SetOutputValue(1.0);
	}
}

void NeuralNet::FeedForward(const vector<double> &inputVals)
{
	assert(inputVals.size() == m_layers[0].size() - 1);

	// Assign the input values into the input Neurons
	for (unsigned i = 0; i < inputVals.size(); ++i)
	{
		m_layers[0][i].SetOutputValue(inputVals[i]);
	}

	// Forward propogate (loop through each layer and Neuron and get them to feed forward)
	for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum)
	{
		Layer &prevLayer = m_layers[layerNum - 1];
		for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n)
		{
			m_layers[layerNum][n].FeedForward(prevLayer);
		}
	}
}

void NeuralNet::BackProp(const vector<double> &targetVals)
{
	// Calculate overall neural net error (Root Mean Square Error of output neuron errors)
	Layer &outputLayer = m_layers.back();
	m_error = 0.0;

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n)
	{
		double delta = targetVals[n] - outputLayer[n].GetOutputValue();
		m_error += delta * delta;
	}
	m_error /= outputLayer.size() - 1; // get average error squared

	// Implement a recent average measurement:
	m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error)
		/ (m_recentAverageSmoothingFactor + 1.0);

	// Calculate output layer gradients
	for (unsigned n = 0; n < outputLayer.size() - 1; ++n)
	{
		outputLayer[n].CalculateOutputGradients(targetVals[n]);
	}

	// Calculate gradients on hidden layers
	for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum)
	{
		Layer &hiddenLayer = m_layers[layerNum];
		Layer &nextLayer = m_layers[layerNum + 1];

		for (unsigned n = 0; n < hiddenLayer.size(); ++n)
		{
			hiddenLayer[n].CalculateHiddenGradients(nextLayer);
		}
	}
	
	// For all layers from outputs to first hidden layer,
	// update connection weights
	for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum)
	{
		Layer &layer = m_layers[layerNum];
		Layer &prevLayer = m_layers[layerNum - 1];

		for (unsigned n = 0; n < layer.size() - 1; ++n)
		{
			layer[n].UpdateInputWeights(prevLayer);
		}
	}
}

void NeuralNet::GetResults(vector<double> &resultVals) const
{
	resultVals.clear();

	for (unsigned n = 0; n < m_layers.back().size() - 1; ++n)
	{
		resultVals.push_back(m_layers.back()[n].GetOutputValue());
	}
}