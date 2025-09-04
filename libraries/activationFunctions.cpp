#include "activationFunctions.h"

#include <cmath>
#include <algorithm>
#include "mathFunctions.h"
#include "matrixUtils.h"

using namespace MatrixUtils; 

/**
 * @brief Sigmoid activation function
 * @param input Input value
 * @return Sigmoid of the input
 */
double sigmoid(const double input) {
	return 1.0 / (1 + exp(-1 * input));
}

/**
 * @brief Derivative of the sigmoid function
 * @param input Input value
 * @return Derivative of the sigmoid at the input
 */
double sigmoid_prime(const double input) {
	return exp(input) * (1 - exp(input));
}

/**
 * @brief ReLU activation function
 * @param input Input value
 * @return ReLU of the input
 */
double relu(const double input) {
	return std::max(0.0,input);
}

/**
 * @brief Derivative of the ReLU function
 * @param input Input value
 * @return Derivative of the ReLU at the input
 */
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

/**
 * @brief Hyperbolic tangent activation function
 * @param input Input value
 * @return tanh of the input
 */
double tan_h(const double input) {
	return tanh(input);
}

/**
 * @brief Derivative of the tanh function
 * @param input Input value
 * @return Derivative of the tanh at the input
 */
double tan_h_prime(const double input) {
	return 1 - pow(input, 2);
}

/**
 * @brief Applies the sigmoid function element-wise to a matrix
 * @param matrix Input matrix
 * @return Matrix with sigmoid applied to each element
 */
Matrix sigmoidPrime(Matrix matrix) {
	Matrix ones(matrix.rows, matrix.cols);
    ones.matrix_fill_with_same_value(1);
	Matrix subtracted = subtract(ones, matrix);
	Matrix multiplied = multiply(matrix, subtracted);
	return multiplied;
}

/**
 * @brief Applies the softmax function element-wise to a matrix
 * @param matrix Input matrix
 * @return Matrix with softmax applied to each element
 */
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

/**
 * @brief Derivative of the softmax function
 * @param sz Size of the square output matrix
 * @param matrix Input matrix (softmax output)
 * @return Jacobian matrix of the softmax function
 */
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

/* Check later */
struct Sigmoid {
    Matrix backwardInput;

    Matrix forward(Matrix input)
    {
        backwardInput = Matrix(input.rows, input.cols);
        backwardInput = input;
        return apply_function(sigmoid, input);
    }

    Matrix backward(Matrix output_gradient, double learning_rate)
    {
        return multiply(output_gradient, apply_function(sigmoid_prime, backwardInput));
    }
};

struct Relu {
    Matrix backwardInput;

    Matrix forward(Matrix input)
    {
        backwardInput = Matrix(input.rows, input.cols);
        backwardInput = input;
        return apply_function(relu, input);
    }

    Matrix backward(Matrix output_gradient, double learning_rate)
    {
        return multiply(output_gradient, apply_function(relu_prime, backwardInput));
    }
};


struct Tanh {
    Matrix backwardInput;

    Matrix forward(Matrix input)
    {
        backwardInput = Matrix(input.rows, input.cols);
        backwardInput = input;
        return apply_function(tan_h, input);
    }

    Matrix backward(Matrix output_gradient, double learning_rate)
    {
        return multiply(output_gradient, apply_function(tan_h_prime, backwardInput));
    }
};

struct Softmax {
    Matrix backwardInput;

    Matrix forward(Matrix input)
    {
        backwardInput = Matrix(input.rows, input.cols);
        backwardInput = input;
        return softmax(input);
    }

    Matrix backward(Matrix output_gradient, double learning_rate)
    {
        Matrix tmp = softmax(backwardInput);
        return dot_product(softmax_prime(backwardInput.rows, tmp), output_gradient);
    }
};
