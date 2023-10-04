#pragma once
#include <vector>
#include <iostream>
#include <random>

typedef double** mat2;

class Array
{
private:
	mat2 _Matrix;
	int _lines;
	int _cols;

	std::default_random_engine _generator;
public:

	Array(int l, int c);
	~Array();
	inline mat2 GetMatrix() { return _Matrix; }
	inline int	GetLines()	{ return _lines; }
	inline int	GetCols()	{ return _cols; }

	template <size_t rows, size_t cols>
	void Define(double(&arr)[rows][cols])
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				_Matrix[i][j] = arr[i][j];
			}
		}
	}
	mat2 DefineMatrix(mat2 z) { _Matrix = z; return z; }

	void Print();
	
	void Randomize();
	void WeightRandomize();
	Array Transpose();
	Array Dot(Array& arr);
	Array LinearDot(Array& arr);
	Array DotScalar(double dot);
	Array Minus(Array& arr);
	Array Sum(Array& arr);
};

