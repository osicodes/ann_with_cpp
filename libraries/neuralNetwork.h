#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "dense.h"

typedef struct NeuralNetwork {

	/// @brief Number of input features
	int input;

    /// @brief Number of hidden neurons
	int hidden;

    /// @brief Number of output neurons
	int output;

    /// @brief Learning rate for training
	double learning_rate;
    
	/// @brief Weights for hidden layer
	Matrix hidden_weights;

    /// @brief Biases for hidden layer
    Matrix hidden_bias;

    /// @brief Weights for output layer
	Matrix output_weights;

    /// @brief Biases for output layer
	Matrix output_bias;

    /// @brief Hidden layer of the neural network
	Dense hidden_layer;

    /// @brief Output layer of the neural network
	Dense output_layer;

    /**
     * @brief Constructor to initialize the neural network with given sizes and learning rate
     * @param input_size Number of input features
     * @param hidden_size Number of hidden neurons
     * @param output_size Number of output neurons
     * @param lr Learning rate for training
     */
    NeuralNetwork(int input_size, int hidden_size, int output_size, double lr)
        : input(input_size), hidden(hidden_size), output(output_size), learning_rate(lr),
          hidden_layer(input_size, hidden_size, "he"), output_layer(hidden_size, output_size, "he"),
          hidden_weights(hidden_layer.weight), hidden_bias(hidden_layer.bias),
          output_weights(output_layer.weight), output_bias(output_layer.bias)
    {
        // Initialize weights and biases if needed
    }
} ;

#endif