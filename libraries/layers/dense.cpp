#include "dense.h"

Dense::Dense(int in, int out, const string &initializationfunc)
    : weight(out, in), bias(out, 1), backwardInput(in, 1), current_layer_neurons(out)
{
    weight.matrix_custom_randomize(weight.rows, weight.cols, initializationfunc);
    bias.matrix_custom_randomize(bias.rows, 1, initializationfunc);
}

Matrix Dense::forward_propagation(const Matrix &input)
{
    check_same_dimensions(input, backwardInput, "Dense layer forward propagation: ");
    backwardInput = input;
    /* Do this later 
    check_column_matrix(input, "Dense layer forward propagation: ");
    weight = Matrix(current_layer_neurons, input.rows);
    backwardInput = input;
    */

    try
    {
        return add(dot_product(weight, input), bias);
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: " << e.what() << endl;
        throw;
    }
    catch (const runtime_error &e)
    {
        cerr << "Runtime error: " << e.what() << '\n';
        throw;
    }
    catch (const std::exception &e)
    {
        cerr << "Standard exception: " << e.what() << '\n';
        throw;
    }
    catch (...)
    {
        cerr << "Unknown exception occurred" << endl;
        throw;
    }
}

Matrix Dense::backward_propagation(const Matrix &output_gradient, const double learning_rate)
{
    Matrix weights_gradient = dot_product(output_gradient, transpose(backwardInput));
    Matrix input_gradient = dot_product(transpose(weight), output_gradient);
    update(weights_gradient, output_gradient, learning_rate);
    return input_gradient;
}

void Dense::update(const Matrix &weights_gradient, const Matrix &output_gradient, const double learning_rate)
{
    weight = subtract(weight, scale(learning_rate, weights_gradient));
    bias = subtract(bias, scale(learning_rate, output_gradient));
}