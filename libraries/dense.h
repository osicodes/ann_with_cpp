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
    Dense(int in, int out, const string &initializationfunc = "he")
        : weight(out, in), bias(out, 1), backwardInput(in, 1)
    {
        weight.matrix_custom_randomize(weight.rows, weight.cols, initializationfunc);
        bias.matrix_custom_randomize(bias.rows, 1, initializationfunc);
    }

    /**
     * @brief Forward pass through the dense layer
     * @param input Input matrix
     * @return Output matrix after applying weights and bias
     */
    Matrix forward_propagation(Matrix input)
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
        }
        catch (const runtime_error &e)
        {
            cerr << "Runtime error: " << e.what() << '\n';
        }
        catch (const std::exception &e)
        {
            cerr << "Standard exception: " << e.what() << '\n';
        }
        catch (...)
        {
            std::cerr << "Unknown exception occurred" << std::endl;
        }
    }

    Matrix backward(Matrix output_gradient,const double learning_rate)
    {
        Matrix weights_gradient = dot_product(output_gradient, transpose(backwardInput));
        Matrix input_gradient = dot_product(transpose(weight), output_gradient);
        weight = subtract(weight,scale(learning_rate,weights_gradient));
        bias = subtract(bias,scale(learning_rate,output_gradient));
        return input_gradient;
    }
};