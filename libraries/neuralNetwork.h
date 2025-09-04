#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "dense.h"

struct NeuralNetwork {

	/// @brief Number of input features
	int input;

    /// @brief Number of hidden neurons
	int hidden;

    /// @brief Number of output neurons
	int output;

    /// @brief Learning rate for training
	double learning_rate;

    /// @brief Hidden layer of the neural network
	Dense hidden_layer;

    /// @brief Output layer of the neural network
	Dense output_layer;
    
	/// @brief Weights for hidden layer
	Matrix hidden_weights;

    /// @brief Biases for hidden layer
    Matrix hidden_bias;

    /// @brief Weights for output layer
	Matrix output_weights;

    /// @brief Biases for output layer
	Matrix output_bias;

    /**
     * @brief Constructor to initialize the neural network with given sizes and learning rate
     * @param input_size Number of input features
     * @param hidden_size Number of hidden neurons
     * @param output_size Number of output neurons
     * @param lr Learning rate for training
     */
    NeuralNetwork(int input_size, int hidden_size, int output_size, double lr);
} ;

#endif