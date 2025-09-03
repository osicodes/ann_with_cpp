#include "activationFunctions.h"

#include <cmath>
#include <algorithm>
#include "mathFunctions.h"

double sigmoid(const double input) {
	return 1.0 / (1 + exp(-1 * input));
}

double sigmoid_prime(const double input) {
	return exp(input) * (1 - exp(input));
}


double relu(const double input) {
	return std::max(0.0,input);
}

double relu_prime(const double input) {
	if (input < 0)
	{
		return 0.0;
	}
	else 
	{
		return 1.0;
	}
	
}

double tan_h(const double input) {
	return tanh(input);
}

double tan_h_prime(const double input) {
	return 1 - pow(input, 2);
}

Matrix sigmoidPrime(Matrix matrix) {
	Matrix ones(matrix.rows, matrix.cols);
    ones.matrix_fill_with_same_value(1);
	Matrix subtracted = subtract(ones, matrix);
	Matrix multiplied = multiply(matrix, subtracted);
	return multiplied;
}

Matrix softmax(Matrix matrix) {
	double total = 0;
	for (int i = 0; i < matrix.rows; i++) {
		for (int j = 0; j < matrix.cols; j++) {
			total += exp(matrix.data[i][j]);
		}
	}
	Matrix result_matrix(matrix.rows, matrix.cols);
	for (int i = 0; i < result_matrix.rows; i++) {
		for (int j = 0; j < result_matrix.cols; j++) {
			result_matrix.data[i][j] = exp(matrix.data[i][j]) / total;
		}
	}
	return result_matrix;
}

Matrix softmax_prime(int sz, Matrix matrix) {
	
	Matrix result_matrix(sz, sz);
	for (int i = 0; i < result_matrix.rows; i++) {
		for (int j = 0; j < result_matrix.cols; j++) {
			if (i == j)
			{
				result_matrix.data[i][j] = matrix.data[i][0] * (1 - matrix.data[j][0]);
			}
			else if (i != j)
			{
				result_matrix.data[i][j]  = -(matrix.data[i][0] * matrix.data[j][0]);
			}
		}
	}
	return result_matrix;
}