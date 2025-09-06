// #include "matrix.h"

#include <iostream>
#include "libraries/functions/mathFunctions.h"
#include "libraries/layers/dense.h"
#include "libraries/neuralNetwork.h"
#include "libraries/layers/reluLayer.h"
#include "libraries/optimizers/sgdOptimizer.h"
#include "libraries/optimizers/adamOptimizer.h"

#include <array>
#include <vector>
using namespace std;

int main()
{
    Matrix m(4, 3);
    Matrix n(4, 3);

    m.matrix_fill_with_same_value(2.2);
    n.matrix_fill_with_same_value(3);

    Matrix sum = add(m, n);
    sum.matrix_print();

    std::vector<std::array<int, 4>> obs_boundarys = {
        {0, 0, 1, 1},
        {1, 1, 2, 2},
        {2, 2, 3, 3}
    };

    vector<vector<double>> X = {
        {1, 2}, 
        {3, 4}
    };
    vector<vector<double>> row1 = {{X.at(0)}}; // Gets {1, 2}
    vector<vector<double>> row2 = {{X[1]}};

    Matrix row1_matrix(1, 2);
    row1_matrix.data = {{X.at(1)}};
    cout << "row of row2_matrix:" << endl;
    row1_matrix.matrix_print();

    // // Using layer structs
    // Dense* denseLayer = new Dense(3, 2);
    // Relu* reluLayer = new Relu();

    Dense denseLayer(3, 2);
    Relu reluLayer = Relu();

    vector<Layer *> layers = {&denseLayer, &reluLayer};
    layers.back()->forward_propagation(m);

    NeuralNetwork nn(layers);
    // nn.compile(ADAM(0.001));
    // nn.fit(m, n, 5, 2);

    

    return 0;
}