// #include "matrix.h"
// https://github.com/lava/matplotlib-cpp/blob/master/README.md
// https://github.com/BobMcDear/neural-network-cuda/blob/main/README.md
// https://github.com/huangzehao/SimpleNeuralNetwork/blob/master/src/neural-net.cpp
// https://github.com/AndrewCarterUK/mnist-neural-network-plain-c/blob/master/neural_network.c

#include <iostream>
#include "libraries/functions/mathFunctions.h"
#include "libraries/layers/dense.h"
#include "libraries/neuralNetwork.h"
#include "libraries/layers/reluLayer.h"
#include "libraries/layers/tanhLayer.h"
#include "libraries/layers/sigmoidLayer.h"
#include "libraries/optimizers/sgdOptimizer.h"
#include "libraries/optimizers/adamOptimizer.h"
#include "csv.h" //https://github.com/ben-strasser/fast-cpp-csv-parser/blob/master/csv.h

#include <array>
#include <vector>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void read_csv(float *inp, string name)
{
    ifstream file(name);
    string line;

    while (getline(file, line, '\n'))
    {
        *inp = stof(line);
        inp++;
    }
}

int main()
{
    srand(time(NULL));

    io::CSVReader<2> in("data/traint.csv");
    in.read_header(io::ignore_extra_column, "x", "y");

    double input;
    double target;
    vector<vector<double>> data;

    while (in.read_row(input, target))
    {
        cout << input << " " << target << endl;
        data.push_back({input, target});
    }

    // cout << "\nPrint data. column size-> " << data.at(0).size() << "\n"
    //      << "------------------" << endl;
    // for (size_t i = 0; i < data.size(); i++)
    // {
    //     for (double eachrow : data[i])
    //         cout << eachrow << " ";
    //     cout<< endl;
    // }

    /*-------------------------------------*/
    io::CSVReader<1> X("data/traintX.csv");
    io::CSVReader<1> Y("data/traintY.csv");

    X.read_header(io::ignore_extra_column, "x");
    Y.read_header(io::ignore_extra_column, "y");

    // double input;
    // double target;
    vector<vector<double>> dataX;
    vector<vector<double>> dataY;

    while (X.read_row(input))
    {
        dataX.push_back({input});
    }

    while (Y.read_row(target))
    {
        dataY.push_back({target});
    }
    /*--------------------------------------------------------*/

    Matrix m(dataX.size(), dataX.at(0).size());
    m.data = dataX;

    Matrix n(dataY.size(), dataY.at(0).size());
    n.data = dataY;

    Matrix sum = add(m, n);
    sum.matrix_print();

    std::vector<std::array<int, 4>> obs_boundarys = {
        {0, 0, 1, 1},
        {1, 1, 2, 2},
        {2, 2, 3, 3}};

    vector<vector<double>> Xt = {
        {1, 2},
        {3, 4}};
    vector<vector<double>> row1 = {{Xt.at(0)}}; // Gets {1, 2}
    vector<vector<double>> row2 = {{Xt[1]}};

    Matrix row1_matrix(1, 2);
    row1_matrix.data = {{Xt.at(1)}};
    // cout << "row of row2_matrix:" << endl;
    // row1_matrix.matrix_print();

    // // Using layer structs
    // Dense* denseLayer = new Dense(3, 2);
    // Relu* reluLayer = new Relu();

    Dense denseLayer1(1, 2);

    Tanh tanhLayer1 = Tanh();
    Dense denseLayer2(2, 1);

    Tanh tanhLayer2 = Tanh();

    vector<Layer *> layers = {&denseLayer1, &tanhLayer1, &denseLayer2, &tanhLayer2};
    // layers.back()->forward_propagation(m);

    NeuralNetwork nn(layers);
    ADAM adam(0.001);
    MSE mse;
    nn.compile(&adam);
    nn.fit(m, n, 2, 3);

    return 0;
}