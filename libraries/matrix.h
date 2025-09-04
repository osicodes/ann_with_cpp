// #pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

#define MAXCHAR 100

struct Matrix
{
private:
    /**
     * @brief Generates a random double within a specified range
     * @param low Lower bound of the range
     * @param high Upper bound of the range
     * @return Random double in the range [low, high)
     */
    double uniform_distribution(double low, double high);

public:
    /// @brief Number of rows in the matrix
    int rows;

    /// @brief Number of columns in the matrix
    int cols;

    /// @brief 2D vector to store matrix data
    vector<vector<double>> data;

    /**
     * Constructor to initialize a matrix with given rows and columns, filled with zeros.
     * @param row Number of rows
     * @param col Number of columns
     */
    Matrix(int row, int col);

    /**
     * Returns a reference to the element at (i, j) allowing it to be modified directly.
     * @param i Row index
     * @param j Column index
     * @return Reference to the element at (i, j)
     * @throws out_of_range if indices are out of bounds
     */
    double &define_value_at(int i, int j);

    /**
     * @brief Prints the matrix to the console in a formatted manner.
     * @note Displays the number of rows and columns followed by the matrix elements.
     */
    void matrix_print();

    /**
     * @brief Fills the entire matrix with the same value.
     * @param number Value to fill the matrix with
     */
    void matrix_fill_with_same_value(double number);

    /**
     * @brief Fills the matrix with values provided by the user.
     * @note Enter each element of the matrix followed by pressing the "Enter" key.
     */
    void matrix_fill_with_value_from_user();

    /**
     * @brief Creates and returns a copy of the current matrix.
     * @return A new Matrix object that is a copy of the current matrix.
     */
    Matrix matrix_copy() const;

    /**
     * @brief Saves the matrix to a text file.
     * @param filename Name of the file to save the matrix to.
     * @note The file will contain the number of rows and columns followed by the matrix elements.
     */
    void matrix_save(const string &filename);

    /**
     * @brief Fills the matrix with random values from a uniform distribution.
     * @param n Number of input neurons (used to determine the range of random values)
     * @note The random values are drawn from the range [-1/sqrt(n), 1/sqrt(n)]
     */
    void matrix_randomize(int n);

    /**
     * @brief Fills the matrix with random values based on the specified initialization method.
     * @param input Number of input neurons (from the previous layer)
     * @param current Number of neurons in the current layer
     * @param initializationfunc Initialization method ("he", "glorot_norm", "glorot_uniform", "leCun")
     * @note Supported initialization methods:
     *       - "he": He Initialization (good for ReLU activation)
     *       - "glorot_norm": Xavier Normalized Initialization (good for other activations)
     *       If an unsupported method is provided, the program will exit with an error message.
     */
    void matrix_custom_randomize(int input, int current, const string &initializationfunc = "he");

    /**
     * @brief Flattens the matrix into a single row or column vector.
     * @param axis Axis along which to flatten (0 for column vector, 1 for row vector)
     * @return Flattened matrix
     * @note Expects a MxN matrix and returns either a (M*N)x1 or 1x(M*N) matrix
     */
    Matrix matrix_flatten(int axis);

    /**
     * @brief Converts a label into a one-hot encoded column vector.
     * @param label Index of the class label
     * @note Expects a Mx1 matrix where M is the number of classes.
     */
    void matrix_column_output(int label);
};

#endif // MATRIX_H