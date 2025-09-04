#pragma once
#include "../matrix.h"
#include "../functions/mathFunctions.h"
#include "../functions/activationFunctions.h"
#include "../matrixUtils.h"
#include "layer.h"

using namespace MatrixUtils;

struct Relu : Layer
{

    /// @brief Input matrix stored for backpropagation
    Matrix backwardInput;

    /**
     * @brief Default constructor for the ReLU layer
     */
    Relu();

    /**
     * @brief Forward pass through the ReLU activation layer
     * @param input Input matrix
     * @return Output matrix after applying ReLU
     */
    Matrix forward_propagation(const Matrix &input);

    /**
     * @brief Backward pass through the ReLU activation layer
     * @param output_gradient Gradient of the loss with respect to the output
     * @param learning_rate Learning rate (not used in ReLU)
     * @return Gradient of the loss with respect to the input
     */
    Matrix backward_propagation(const Matrix &output_gradient, double);

protected:
    void update(const Matrix &,
                const Matrix &,
                const double) override
    {
    }
};