#include "tanhLayer.h"

Matrix Tanh::forward_propagation(const Matrix &input)
{
    backwardInput = Matrix(input.rows, input.cols);
    backwardInput = input;
    return apply_function(tan_h, input);
}

Matrix Tanh::backward_propagation(const Matrix &output_gradient, double)
{
    // cout << "\n output_gradient in tanh" << endl;
    // output_gradient.matrix_copy().matrix_print();

    return multiply(output_gradient, apply_function(tan_h_prime, backwardInput));
}