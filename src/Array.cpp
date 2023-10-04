#include "Array.h"

Array::Array(int l, int c)
	: _lines(l), _cols(c)
{
	srand(static_cast <unsigned> (time(0)));

	_Matrix = (mat2)_malloca(l * sizeof(double*));
	if (_Matrix)
	{
		for (int i = 0; i < l; i++)
		{
			_Matrix[i] = (double*)_malloca(c * sizeof(double));
		}

		for (int i = 0; i < l; i++)
		{
			for (int j = 0; j < c; j++)
			{
				(_Matrix[i] ? _Matrix[i][j] = 0.0f : NULL);
			}
		}
	}
}


Array::~Array() { }

void Array::Print()
{

	for (int i = 0; i < _lines; i++)
	{
		for (int j = 0; j < _cols; j++)
		{
			std::cout << _Matrix[i][j] << " ";
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}


void Array::Randomize()
{
	for (int i = 0; i < _lines; i++)
	{
		for (int j = 0; j < _cols; j++)
		{
			_Matrix[i][j] = (double(rand()) / double((RAND_MAX)));
		}
	}
}

void Array::WeightRandomize()
{
	double attrib = pow(_lines, -2);
	std::normal_distribution<double> distribution(0.0, attrib);
	for (int i = 0; i < _lines; i++)
	{
		for (int j = 0; j < _cols; j++)
		{
			_Matrix[i][j] = distribution(_generator);
		}
	}
}

Array Array::Transpose()
{
	Array temp_matrix(_cols, _lines);
	mat2 temp = temp_matrix.GetMatrix();

	for (int i = 0; i < _lines; i++)
	{
		for (int j = 0; j < _cols; j++)
		{
			temp[j][i] = _Matrix[i][j];
		}
	}

	temp_matrix.DefineMatrix(temp);
	return temp_matrix;
}


Array Array::Dot(Array& arr)
{
	if (_cols == arr.GetLines()) 
	{
		Array matrix_multiplier(_lines, arr.GetCols());
		mat2 multiplier = matrix_multiplier.GetMatrix();;
		for (int i = 0; i < _lines; i++)
		{
			for (int j = 0; j < arr.GetCols(); j++)
			{
				for (int k = 0; k < _cols; k++)
				{
					multiplier[i][j] += _Matrix[i][k] * arr.GetMatrix()[k][j];
				}
			}
		}
		matrix_multiplier.DefineMatrix(multiplier);
		return matrix_multiplier;
	}
	else
	{
		std::cout << "[ERROR] Could not broadcast arrays [OPERATION: DOT]" << "(" << _lines << ", " << _cols << ") and (" << arr.GetLines() << ", " << arr.GetCols() << ").\n";
		Array y(1, 1);
		return y;
	}
}


Array Array::Minus(Array& arr)
{
	if (_lines == arr.GetLines() and _cols == arr.GetCols())
	{
		Array matrix_minus(_lines, _cols);
		mat2 minus = matrix_minus.GetMatrix();
		{
			for (int i = 0; i < _lines; i++)
				for (int j = 0; j < _cols; j++)
				{
					minus[i][j] = _Matrix[i][j] - arr.GetMatrix()[i][j];
				}
		}
		matrix_minus.DefineMatrix(minus);
		return matrix_minus;
	}
	else
	{
		std::cout << "[ERROR] Could not broadcast arrays [OPERATION: MINUS] " << "(" << _lines << ", " << _cols << ") and (" << arr.GetLines() << ", " << arr.GetCols() << ").\n";
		Array y(1, 1);
		return y;
	}
}

Array Array::Sum(Array& arr)
{
	if (_lines == arr.GetLines() and _cols == arr.GetCols())
	{
		Array matrix_sum(_lines, _cols);
		mat2 sum = matrix_sum.GetMatrix();
		{
			for (int i = 0; i < _lines; i++)
				for (int j = 0; j < _cols; j++)
				{
					sum[i][j] = _Matrix[i][j] + arr.GetMatrix()[i][j];
				}
		}
		matrix_sum.DefineMatrix(sum);
		return matrix_sum;
	}
	else
	{
		std::cout << "[ERROR] Could not broadcast arrays [OPERATION: SUM] " << "(" << _lines << ", " << _cols << ") and (" << arr.GetLines() << ", " << arr.GetCols() << ").\n";
		Array y(1, 1);
		return y;
	}
}

Array Array::DotScalar(double dot)
{
	if (_Matrix)
	{
		Array matrix_dot_scalar(_lines, _cols);
		mat2 scalar = matrix_dot_scalar.GetMatrix();
		{
			for (int i = 0; i < _lines; i++)
				for (int j = 0; j < _cols; j++)
				{
					scalar[i][j] = _Matrix[i][j] * dot;
				}
		}
		matrix_dot_scalar.DefineMatrix(scalar);
		return matrix_dot_scalar;
	}
}

Array Array::LinearDot(Array& arr)
{
	if (_lines == arr.GetLines() and _cols == arr.GetCols())
	{
		Array matrix_linear_dot(_lines, _cols);
		mat2 linear_dot = matrix_linear_dot.GetMatrix();
		{
			for (int i = 0; i < _lines; i++)
				for (int j = 0; j < _cols; j++)
				{
					linear_dot[i][j] = _Matrix[i][j] * arr.GetMatrix()[i][j];
				}
		}
		matrix_linear_dot.DefineMatrix(linear_dot);
		return matrix_linear_dot;
	}
	else
	{
		std::cout << "[ERROR] Could not broadcast arrays [OPERATION: LINEAR DOT]" << "(" << _lines << ", " << _cols << ") and (" << arr.GetLines() << ", " << arr.GetCols() << ").\n";
		Array y(1, 1);
		return y;
	}
}