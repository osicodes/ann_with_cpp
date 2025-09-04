#include "softmaxLayer.h"

Matrix Softmax::forward_propagation(const Matrix &input)
{
    backwardInput = Matrix(input.rows, input.cols);
    backwardInput = input;
    return softmax(input);
}

Matrix Softmax::backward_propagation(const Matrix &output_gradient, double)
{
    Matrix tmp = softmax(backwardInput);
    return dot_product(softmax_prime(backwardInput.rows, tmp), output_gradient);
}