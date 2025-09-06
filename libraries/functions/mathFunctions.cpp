#include "mathFunctions.h"
// #include <stdlib.h>
// #include <stdio.h>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>
#include "../matrixUtils.h"
using namespace std;
using namespace MatrixUtils;

/**
 * @brief Element-wise multiplication of two matrices
 * @param matrix1 First matrix
 * @param matrix2 Second matrix
 * @return Resultant matrix after multiplication
 * @throws invalid_argument: Dimension mistmatch multiply
 */
Matrix multiply(const Matrix &matrix1, const Matrix &matrix2)
{
	MatrixUtils::check_same_dimensions(matrix1, matrix2, "Dimension mismatch multiply: ");
	Matrix result_matrix(matrix1.rows, matrix1.cols);
	for (int i = 0; i < matrix1.rows; i++)
	{
		for (int j = 0; j < matrix2.cols; j++)
		{
			result_matrix.data[i][j] = matrix1.data[i][j] * matrix2.data[i][j];
		}
	}
	return result_matrix;
}

/**
 * @brief Matrix multiplication (dot product) of two matrices
 * @param matrix1 First matrix
 * @param matrix2 Second matrix
 * @return Resultant matrix after multiplication
 * @throws invalid_argument: Dimension mistmatch dot_product
 */
Matrix dot_product(const Matrix &matrix1, const Matrix &matrix2)
{
	check_dot_product_compatible(matrix1, matrix2, "Dimension mistmatch dot_product: ");

	Matrix result_matrix(matrix1.rows, matrix2.cols);
	for (int i = 0; i < matrix1.rows; i++)
	{
		for (int j = 0; j < matrix2.cols; j++)
		{
			double sum = 0.0;
			for (int k = 0; k < matrix2.rows; k++)
			{
				sum += matrix1.data[i][k] * matrix2.data[k][j];
			}
			result_matrix.data[i][j] = sum;
		}
	}
	return result_matrix;
}

/**
 * @brief Element-wise addition of two matrices
 * @param matrix1 First matrix
 * @param matrix2 Second matrix
 * @return Resultant matrix after addition
 * @throws invalid_argument: Dimension mistmatch add
 */
Matrix add(const Matrix &matrix1, const Matrix &matrix2)
{
	check_same_dimensions(matrix1, matrix2, "Dimension mistmatch add: ");

	Matrix result_matrix(matrix1.rows, matrix1.cols);
	for (int i = 0; i < matrix1.rows; i++)
	{
		for (int j = 0; j < matrix2.cols; j++)
		{
			result_matrix.data[i][j] = matrix1.data[i][j] + matrix2.data[i][j];
		}
	}
	return result_matrix;
}

/**
 * @brief Element-wise subtraction of two matrices
 * @param matrix1 First matrix
 * @param matrix2 Second matrix
 * @return Resultant matrix after subtraction
 * @throws invalid_argument: Dimension mistmatch subtract
 */
Matrix subtract(const Matrix &matrix1, const Matrix &matrix2)
{
	check_same_dimensions(matrix1, matrix2, "Dimension mistmatch subtract: ");

	Matrix result_matrix(matrix1.rows, matrix1.cols);
	for (int i = 0; i < matrix1.rows; i++)
	{
		for (int j = 0; j < matrix2.cols; j++)
		{
			result_matrix.data[i][j] = matrix1.data[i][j] - matrix2.data[i][j];
		}
	}
	return result_matrix;
}

/**
 * @brief Prepares a matrix for softmax by subtracting the maximum value from each element
 * @param matrix Input matrix
 * @return New matrix with maximum value subtracted from each element
 */
Matrix beforeSoftmax(const Matrix &matrix)
{
	double maxnum = matrix_argmax(matrix);

	Matrix result_matrix(matrix.rows, matrix.cols);
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			result_matrix.data[i][j] = matrix.data[i][j] - maxnum;
		}
	}
	return result_matrix;
}

/**
 * @brief Generates an identity matrix of given size
 * @param num Size of the identity matrix (num x num)
 * @return Identity matrix
 */
Matrix identity_matrix(const int &num)
{
	int row, col;
	Matrix result_matrix(num, num);
	for (row = 0; row < num; row++)
	{
		for (col = 0; col < num; col++)
		{
			// Checking if row is equal to column
			if (row == col)
				result_matrix.data[row][col] = 1.0;
			else
				result_matrix.data[row][col] = 0.0;
		}
	}
	return result_matrix;
}

/**
 * @brief Scales each element of the matrix by a given factor
 * @param scale_value Scaling factor
 * @param matrix Input matrix
 * @return New matrix with each element scaled
 */
Matrix scale(const double &scale_value, const Matrix &matrix)
{
	Matrix result_matrix = matrix.matrix_copy();
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			result_matrix.data[i][j] *= scale_value;
		}
	}
	return result_matrix;
}

/**
 * @brief Adds a scalar value to each element of the matrix
 * @param scale_value Scalar value to be added
 * @param matrix Input matrix
 * @return New matrix with the scalar added to each element
 */
Matrix addScalar(const double &scale_value, const Matrix &matrix)
{
	Matrix result_matrix = matrix.matrix_copy();
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			result_matrix.data[i][j] += scale_value;
		}
	}
	return result_matrix;
}

/**
 * @brief Transposes the given matrix
 * @param matrix Input matrix
 * @return Transposed matrix
 */
Matrix transpose(const Matrix &matrix)
{
	Matrix result_matrix(matrix.cols, matrix.rows);
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			result_matrix.data[j][i] = matrix.data[i][j];
		}
	}
	return result_matrix;
}

/**
 * @brief Calculates the determinant of a square matrix
 * @param matrix Input square matrix
 * @return Determinant value
 * @throws runtime_error: If the matrix is not square
 */
double determinant(const Matrix &matrix)
{
	check_square_matrix(matrix, "Determinant calculation");
	// Determinant implementation here
	return 0.0; // Placeholder return value
}

/**
 * @brief Returns the index of the maximum value in a single-column matrix.
 * @return Index of the maximum value
 * @note Expects a Mx1 matrix
 */
double matrix_argmax(const Matrix &matrix)
{
	try
	{
		check_column_matrix(matrix, "matrix_argmax: Dimension error: ");
		double max_score = 0;
		int max_index = 0;
		for (int i = 0; i < matrix.rows; i++)
		{
			if (matrix.data[i][0] > max_score)
			{
				max_score = matrix.data[i][0];
				max_index = i;
			}
		}
		return max_index;
	}
	catch (const invalid_argument &e)
	{
		cerr << "Error: " << e.what() << endl;
	}
	catch (const std::exception &e)
	{
		cerr << "Standard exception: " << e.what() << '\n';
	}
	catch (...)
	{
		std::cerr << "Unknown exception occurred" << std::endl;
	}
	return 0;
}

/**
 * @brief Calculates the Cross Entropy Error between two matrices
 * @param m1 First matrix (true values)
 * @param m2 Second matrix (predicted values)
 * @return Cross Entropy Error value
 */
double cross_enthropy(const Matrix m1, const Matrix m2)
{
	// Cross Enthropy Error
	check_same_dimensions(m1, m2, "Dimension mistmatch Cross Enthropy Error:");
	// true_y * log(predicted_y)
	double error = 0.0;
	for (int i = 0; i < m1.rows; i++)
	{
		for (int j = 0; j < m2.cols; j++)
		{
			error += m1.data[i][j] * log(m2.data[i][j]);
		}
	}
	return -1 * error;
}

/**
 * @brief Calculates the derivative of the Cross Entropy Error with respect to the predicted values
 * @param m1 First matrix (true values)
 * @param m2 Second matrix (predicted values)
 * @return Matrix representing the derivative of Cross Entropy Error
 */
Matrix cross_enthropy_derivative(const Matrix &m1, const Matrix &m2)
{
	Matrix output = subtract(m2, m1); // predicted_y  - true_y
	return output;
}