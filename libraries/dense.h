#pragma once
#include "matrix.h"
#include "mathFunctions.h"
#include "matrixUtils.h"
using namespace MatrixUtils;

struct Dense
{
    /// @brief Weight matrix of the dense layer
    Matrix weight;

    /// @brief Bias vector of the dense layer
    Matrix bias;

    /// @brief Input matrix stored for backpropagation
    Matrix backwardInput;

    /**
     * @brief Constructor to initialize the dense layer with given input and output sizes
     * @param in Number of input features
     * @param out Number of output features
     * @param initializationfunc Initialization method ("he", "glorot_norm", "glorot_uniform", "leCun")
     */
    Dense(int in, int out, const string &initializationfunc = "he");

    /**
     * @brief Forward pass through the dense layer
     * @param input Input matrix
     * @return Output matrix after applying weights and bias
     */
    Matrix forward_propagation(Matrix input);

    /**
     * @brief Backward pass through the dense layer
     * @param output_gradient Gradient of the loss with respect to the output
     * @param learning_rate Learning rate for weight updates
     * @return Gradient of the loss with respect to the input
     */
    Matrix backward(Matrix output_gradient, const double learning_rate);
};