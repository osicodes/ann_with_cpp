#include "dense.h"

Dense::Dense(int in, int out, const string &initializationfunc)
    : weight(out, in), bias(out, 1), backwardInput(in, 1)
{
    weight.matrix_custom_randomize(weight.rows, weight.cols, initializationfunc);
    bias.matrix_custom_randomize(bias.rows, 1, initializationfunc);
}

Matrix Dense::forward_propagation(Matrix input)
{
    check_same_dimensions(input, backwardInput, "Dense layer forward propagation: ");
    backwardInput = input;

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

Matrix Dense::backward(Matrix output_gradient, const double learning_rate)
{
    Matrix weights_gradient = dot_product(output_gradient, transpose(backwardInput));
    Matrix input_gradient = dot_product(transpose(weight), output_gradient);
    weight = subtract(weight, scale(learning_rate, weights_gradient));
    bias = subtract(bias, scale(learning_rate, output_gradient));
    return input_gradient;
}