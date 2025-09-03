#pragma once
#include "matrix.h"
#include "mathFunctions.h"

typedef struct Dense
{
    /// @brief Weight matrix of the dense layer
    Matrix weight;

    /// @brief Bias vector of the dense layer
    Matrix bias;

    /// @brief Input matrix stored for backpropagation
    Matrix backwardInput;
    Dense(int in, int out, const char *initializationfunc)
        : weight(out, in), bias(out, 1), backwardInput(in, 1)
    {
    }

    /**
     * @brief Forward pass through the dense layer
     * @param input Input matrix
     * @return Output matrix after applying weights and bias
     */
    Matrix forward(Matrix input)
    {
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
};