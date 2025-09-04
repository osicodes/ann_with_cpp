#include "reluLayer.h"

Relu::Relu() {}

Matrix Relu::forward_propagation(const Matrix &input)
{
    backwardInput = Matrix(input.rows, input.cols);
    backwardInput = input;
    return apply_function(relu, input);
}

Matrix Relu::backward_propagation(const Matrix &output_gradient, double)
{
    return multiply(output_gradient, apply_function(relu_prime, backwardInput));
}