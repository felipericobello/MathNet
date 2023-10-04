#pragma once
#include "Array.h"
#include <cmath>

class NeuralNetwork
{
public:
	NeuralNetwork(unsigned int input_nodes, unsigned int hidden_nodes, unsigned int output_nodes, double learning_rate);
	~NeuralNetwork();

	Array ActivationFunction(Array& z) 
	{
		Array activation(z.GetLines(), z.GetCols());
		mat2 temp_matrix = activation.GetMatrix();

		for (int i = 0; i < z.GetLines(); i++)
			for (int j = 0; j < z.GetCols(); j++)
			{
				temp_matrix[i][j] = 1.0 / (1.0 + std::exp((- 1.0)*z.GetMatrix()[i][j]));
			}
		activation.DefineMatrix(temp_matrix);
		return activation;
	}

	Array AuxiliarFunction(Array& z)
	{
		Array aux(z.GetLines(), z.GetCols());
		mat2 temp_matrix = aux.GetMatrix();

		for (int i = 0; i < z.GetLines(); i++)
			for (int j = 0; j < z.GetCols(); j++)
			{
				temp_matrix[i][j] = z.GetMatrix()[i][j] * (1.0 - z.GetMatrix()[i][j]);
			}
		aux.DefineMatrix(temp_matrix);
		return aux;
	}

	template <size_t irows, size_t icols, size_t orows, size_t ocols>
	void Train(double(&input_list)[irows][icols], double(&target_list)[orows][ocols], unsigned int epoch)
	{
		//INPUT AND TARGET DEFINITION:
		Array input(irows, icols);
		Array target(orows, ocols);

		input.Define(input_list);
		target.Define(target_list);

		//WEIGHTS GENERATION:
		Array weightsIH(_inodes, _hnodes);
		Array weightsHO(_hnodes, _onodes);
		weightsIH.WeightRandomize();
		weightsHO.WeightRandomize();

		//TRAINING LOOP:
		for (int e = 0; e < epoch; e++)
		{
			if (e % 100 == 0)
			{
				std::cout << "Epoch: " << e << '\n';
			}
			Array inputT  = input.Transpose();
			Array targetT = target.Transpose();
			Array wIHT    = weightsIH.Transpose();
			Array wOHT	  = weightsHO.Transpose();


			Array hidden_inputs  = wIHT.Dot(inputT);
			Array hidden_outputs = ActivationFunction(hidden_inputs);

			Array final_inputs   = wOHT.Dot(hidden_outputs);
			Array final_outputs  = ActivationFunction(final_inputs);

			Array loss = targetT.Minus(final_outputs);
			Array hidden_loss = weightsHO.Dot(loss);


			Array dck = AuxiliarFunction(final_outputs);
			dck = loss.LinearDot(dck);

			Array dcj = AuxiliarFunction(hidden_outputs);
			dcj = hidden_loss.LinearDot(dcj);


			Array hidden_outputsT = hidden_outputs.Transpose();

			Array delta_wHO = dck.Dot(hidden_outputsT);
			delta_wHO = delta_wHO.DotScalar(_lr);
			Array delta_wHOT = delta_wHO.Transpose();
			weightsHO = weightsHO.Sum(delta_wHOT);

			Array delta_wIH = dcj.Dot(input);
			delta_wIH = delta_wIH.DotScalar(_lr);
			Array delta_wIHT = delta_wIH.Transpose();
			weightsIH = weightsIH.Sum(delta_wIHT);

		}
		_weightsIH->DefineMatrix(weightsIH.GetMatrix());
		_weightsHO->DefineMatrix(weightsHO.GetMatrix());
	}

	template <size_t rows, size_t cols>
	void Predict(double(&input_list)[rows][cols])
	{
		Array input(rows, cols);
		input.Define(input_list);

		Array inputT = input.Transpose();
		Array wIHT = _weightsIH->Transpose();
		Array wOHT = _weightsHO->Transpose();

		Array hidden_inputs = wIHT.Dot(inputT);
		Array hidden_outputs = ActivationFunction(hidden_inputs);

		Array final_inputs = wOHT.Dot(hidden_outputs);
		Array final_outputs = ActivationFunction(final_inputs);

		final_outputs.Print();
	}

private:
	Array* _weightsIH;
	Array* _weightsHO;
	unsigned int _inodes, _hnodes, _onodes;
	float _lr;
};

