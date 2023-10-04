#include <iostream>
#include "NeuralNetwork.h"
#include "Array.h"

int main()
{	
	double inputs[4][2] = { {0.01, 0.01}, {0.01, 0.99}, {0.99, 0.01}, {0.99, 0.99} };
	double desiredOutputs[4][1] = { {0.01}, {0.99}, {0.99}, {0.99} };

	NeuralNetwork model(2, 3, 1, 0.2);
	model.Train(inputs, desiredOutputs, 300000);
	model.Predict(inputs);
}