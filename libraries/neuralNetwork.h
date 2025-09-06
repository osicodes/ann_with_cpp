#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "layers/dense.h"
#include "optimizers/optimizer.h"
#include "optimizers/sgdOptimizer.h"
#include "loss/mse.h"

struct NeuralNetwork
{
private:
    void train();
    Matrix perform_forward_propagation(const Matrix &input);
    void perform_backward_propagation(const Matrix &loss_gradient, const double learning_rate);

public:
    /// @brief Number of input features
    int input;

    /// @brief Number of hidden neurons
    int hidden;

    /// @brief Number of output neurons
    int output;

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

    /// @brief Vector of pointers to layers in the network
    vector<Layer *> layers;

    int epochSize;

    int batchSize;

    /// @brief Input data matrix
    Matrix input_data;

    /// @brief Target data matrix
    Matrix target_data;

    /// @brief Optimizer for training the network   
    Optimizer optimizer;

    /// @brief Loss function for training the network
    Loss loss;

    /**
     * @brief Constructor to initialize the neural network with given layers
     * @param _layers Vector of pointers to Layer objects
     * @note The layers should be added in the order they are to be used in the network
     */
    NeuralNetwork(vector<Layer *> _layers);

    /**
     * @brief Compiles the neural network by setting the learning rate
     * @param lr Learning rate for training
     */
    void compile(Optimizer optimizer_type = SGD(), Loss loss_function = MSE());

    /**
     * @brief Performs a forward pass through the network
     * @param input Input data matrix
     * @return Output matrix after passing through all layers
     */
    void fit(const Matrix &input, const Matrix &target, int epochs = 10, int batch_size = 10);
};

#endif