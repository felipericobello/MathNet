#include "NeuralNetwork.h"
NeuralNetwork::NeuralNetwork(unsigned int input_nodes, unsigned int hidden_nodes, unsigned int output_nodes, double learning_rate)
	: _inodes(input_nodes), _hnodes(hidden_nodes), _onodes(output_nodes), _lr(learning_rate)
{ 
	_weightsIH = new Array(_inodes, _hnodes);
	_weightsHO = new Array(_hnodes, _onodes);
}

NeuralNetwork::~NeuralNetwork()
{}
