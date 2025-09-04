#include "neuralNetwork.h"


NeuralNetwork::NeuralNetwork(int input_size, int hidden_size, int output_size, double lr)
    : input(input_size), hidden(hidden_size), output(output_size), learning_rate(lr),
      hidden_layer(input_size, hidden_size, "he"), output_layer(hidden_size, output_size, "he"),
      hidden_weights(hidden_layer.weight), hidden_bias(hidden_layer.bias),
      output_weights(output_layer.weight), output_bias(output_layer.bias)
{
    // Initialize weights and biases if needed
}