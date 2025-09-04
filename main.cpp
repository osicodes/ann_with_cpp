// #include "matrix.h"

#include <iostream>
#include "mathFunctions.h"
#include "dense.h"
#include "neuralNetwork.h"
#include "reluLayer.h"
using namespace std;

int main() {
    Matrix m(4, 3);
    Matrix n(4, 3);
    
    m.matrix_fill_with_same_value(2.2);
    n.matrix_fill_with_same_value(3);

    Matrix sum = add(m, n);
    sum.matrix_print();

    // // Using layer structs
    // Dense* denseLayer = new Dense(3, 2);
    // Relu* reluLayer = new Relu();
    
    Dense denseLayer(3, 2);
    Relu reluLayer = Relu();


    vector<Layer*> layers = {&denseLayer, &reluLayer};
    layers.back()->forward_propagation(m);

    NeuralNetwork nn(layers);
    nn.compile(0.01);


    return 0;
}