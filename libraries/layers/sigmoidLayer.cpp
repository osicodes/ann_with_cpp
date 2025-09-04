#include "sigmoidLayer.h"

Matrix Sigmoid::forward_propagation(const Matrix &input)
{
    backwardInput = Matrix(input.rows, input.cols);
    backwardInput = input;
    return apply_function(sigmoid, input);
}

Matrix Sigmoid::backward_propagation(const Matrix &output_gradient, double)
{
    return multiply(output_gradient, apply_function(sigmoid_prime, backwardInput));
}