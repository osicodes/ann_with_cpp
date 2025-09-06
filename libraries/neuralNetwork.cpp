#include "neuralNetwork.h"

// NeuralNetwork::NeuralNetwork(int input_size, int hidden_size, int output_size, double lr)
//     : input(input_size), hidden(hidden_size), output(output_size), learning_rate(lr),
//       hidden_layer(input_size, hidden_size, "he"), output_layer(hidden_size, output_size, "he"),
//       hidden_weights(hidden_layer.weight), hidden_bias(hidden_layer.bias),
//       output_weights(output_layer.weight), output_bias(output_layer.bias)
// {
//     // Initialize weights and biases if needed
// }

NeuralNetwork::NeuralNetwork(vector<Layer *> _layers)
{
    layers = _layers;
}

void NeuralNetwork::compile(Optimizer optimizer_type, Loss loss_function)
{
    optimizer = optimizer_type;
    loss = loss_function;
}

void NeuralNetwork::fit(const Matrix &input, const Matrix &target, int epochs, int batch_size)
{
    input_data = input;
    target_data = target;
    epochSize = epochs;
    batchSize = batch_size;

    for (int i = 0; i < epochSize; i++)
    {
        cout << "Epoch " << i + 1 << "/" << epochSize << endl;
        train();
    }
}

void NeuralNetwork::train()
{
    int input_data_size_rows = input_data.rows;
    int input_data_size_cols = input_data.cols;
    
    int target_data_size_rows = target_data.rows;
    int target_data_size_cols = target_data.cols;
    for (int i = 0; i < input_data_size_rows; i += batchSize)
    {
        int actualBatchSize = min(batchSize, input_data_size_rows - i);

        for (int j = 0; j < actualBatchSize; j++)
        {
            int idx = i + j;
            Matrix each_row_of_input_data = Matrix(1, input_data_size_cols);
            each_row_of_input_data.data = {{input_data.data[idx]}};

            Matrix each_row_of_target_data = Matrix(1, target_data_size_cols);
            each_row_of_target_data.data = {{target_data.data[idx]}};

            Matrix result = perform_forward_propagation(transpose(each_row_of_input_data));

            loss.forward(transpose(each_row_of_target_data), result);
            Matrix loss_gradient = loss.backward();

            perform_backward_propagation(loss_gradient, optimizer.learning_rate);

            cout << "Output after forward propagation for sample " << idx + 1 << ": ";
        }
    }
}

Matrix NeuralNetwork::perform_forward_propagation(const Matrix &input)
{
    Matrix output = input;
    for (Layer *layer : layers)
    {
        output = layer->forward_propagation(output);
    }
    return output;
}

void NeuralNetwork::perform_backward_propagation(const Matrix &loss_gradient, const double learning_rate)
{
    Matrix output_gradient = loss_gradient;
    for (auto it = layers.rbegin(); it != layers.rend(); ++it)
    {
        output_gradient = (*it)->backward_propagation(output_gradient, learning_rate);
    }
}