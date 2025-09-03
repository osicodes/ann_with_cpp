// #pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

#define MAXCHAR 100

struct Matrix
{
private:
    /**
     * @brief Generates a random double within a specified range
     * @param low Lower bound of the range
     * @param high Upper bound of the range
     * @return Random double in the range [low, high)
     */
    double uniform_distribution(double low, double high)
    {

        static double difference = high - low; // The difference between the two
        static int scale = 10000;              // Scaling factor to convert to integer range
        static int scaled_difference = (int)(difference * scale);
        return low + (1.0 * (rand() % scaled_difference) / scale);
    }

public:
    /// @brief Number of rows in the matrix
    int rows;

    /// @brief Number of columns in the matrix
    int cols;

    /// @brief 2D vector to store matrix data
    vector<vector<double>> data;

    /**
     * Constructor to initialize a matrix with given rows and columns, filled with zeros.
     * @param row Number of rows
     * @param col Number of columns
     */
    Matrix(int row, int col) : rows(row), cols(col), data(row, vector<double>(col, 0.0))
    {
    }

    /**
     * Returns a reference to the element at (i, j) allowing it to be modified directly.
     * @param i Row index
     * @param j Column index
     * @return Reference to the element at (i, j)
     * @throws out_of_range if indices are out of bounds
     */
    double &define_value_at(int i, int j)
    {
        return data.at(i).at(j);
    }

    /**
     * Prints the matrix to the console in a formatted manner.
     */
    void matrix_print()
    {
        cout << "Rows: " << rows << " Columns: " << cols << endl;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << fixed << setprecision(5) << setw(1) << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    /**
     * @brief Fills the entire matrix with the same value.
     * @param number Value to fill the matrix with
     */
    void matrix_fill_with_same_value(double number)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                data.at(i).at(j) = number;
            }
        }
    }

    /**
     * @brief Fills the matrix with values provided by the user.
     * @note Enter each element of the matrix followed by pressing the "Enter" key.
     */
    void matrix_fill_with_value_from_user()
    {
        double a;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << "Enter element [" << i << "][" << j << "]: ";
                cin >> a;
                data.at(i).at(j) = a;
            }
        }
    }

    /**
     * @brief Creates and returns a copy of the current matrix.
     * @return A new Matrix object that is a copy of the current matrix.
     */
    Matrix matrix_copy() const
    {
        return *this;
    }

    /**
     * @brief Saves the matrix to a text file.
     * @param filename Name of the file to save the matrix to.
     * @note The file will contain the number of rows and columns followed by the matrix elements.
     */
    void matrix_save(const string &filename)
    {
        ofstream file(filename);

        if (!file)
        {
            cerr << "Error: Cannot open file " << filename << endl;
            return;
        }

        file << "Rows: " << rows << " Columns: " << cols << "\n";

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                file << data[i][j] << " ";
            }
            file << "\n";
        }
        cout << "Successfully saved matrix to " << filename;
    }

    /**
     * @brief Fills the matrix with random values from a uniform distribution.
     * @param n Number of input neurons (used to determine the range of random values)
     * @note The random values are drawn from the range [-1/sqrt(n), 1/sqrt(n)]
     */
    void matrix_randomize(int n)
    {
        double min = -1.0 / sqrt(n);
        double max = 1.0 / sqrt(n);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                data[i][j] = uniform_distribution(min, max);
            }
        }
    }

    /**
     * @brief Fills the matrix with random values based on the specified initialization method.
     * @param input Number of input neurons (from the previous layer)
     * @param current Number of neurons in the current layer
     * @param initializationfunc Initialization method ("he", "glorot_norm", "glorot_uniform", "leCun")
     * @note Supported initialization methods:
     *       - "he": He Initialization (good for ReLU activation)
     *       - "glorot_norm": Xavier Normalized Initialization (good for other activations)
     *       If an unsupported method is provided, the program will exit with an error message.
     */
    void matrix_custom_randomize(int input, int current, const string &initializationfunc) {
        /*
        input -->  Number of nodes/neurons in input or previous layer (or number of input neurons coming into this current layer)
        current -->  Number of nodes/neurons in current layer (not input or previous layer)
        size_l = current;
        size_l_minus_1 = input;

        LeCun  Initialization (Good for SELU activation functions )
        ----------------------
        Min: -1 / sqrt(input)
        Max: 1 / sqrt(input)
        ---------------------


        Xavier normalized initialization  (Good for other activation functions{Linear, sigmoid/logistics, tanh, softmax, },
                                                        but not very good for RELU)
        sqrt(1 / ave)
        ave = (input + current) / 2
        ----------------------
        Min: -sqrt(2 / (size_l_minus_1 + size_l))
        Max: sqrt(2 / (size_l_minus_1 + size_l))
        ---------------------


        Xavier uniform initialization
        ----------------------
        Min: -(sqrt(6.0) / sqrt(size_l_minus_1 + size_l))
        Max: (sqrt(6.0) / sqrt(size_l_minus_1 + msize_l))
        ---------------------


        He Initialization (Good for RELU activation functions )
        ----------------------
        Min: -sqrt(2/input)
        Max: sqrt(2/input))
        ---------------------

        For  Hyperbolic tangent activation function, tanh(x)
        standard deviation (v) = 1 / sqrt(ave)
        ave = (input + current) / 2

        For  Sigmoid/logistics activation function, 1 / (1 + exp(-x))
        standard deviation (v) = 3.6 / sqrt(input)

        For  RELU activation function, max(0,x)
        standard deviation (v) = sqrt(2/input)

        References
        -------------------------------------
        http://proceedings.mlr.press/v9/glorot10a/glorot10a.pdf
        https://arxiv.org/pdf/1704.08863.pdf   page 3.
        https://arxiv.org/abs/1502.01852
        https://bit.ly/3ehISpn
        http://ufldl.stanford.edu/tutorial/supervised/MultiLayerNeuralNetworks/
        https://www.youtube.com/watch?v=tYFO434Lpm0
        */
        int size_l = current;
        int size_l_minus_1 = input;

        if (initializationfunc == "he")
        {
            double min = -sqrt(2) / sqrt(size_l_minus_1);
            double max = sqrt(2) / sqrt(size_l_minus_1);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    data[i][j] = uniform_distribution(min, max);
                }
            }
        }
        else if (initializationfunc == "glorot_norm")
        {
            double min = -sqrt(2) / sqrt(size_l_minus_1 + size_l);
            double max = sqrt(2) / sqrt(size_l_minus_1 + size_l);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    data[i][j] = uniform_distribution(min, max);
                }
            }
        }
        else
        {
            cout << initializationfunc << " is not a supported initialization method" << endl;
            exit(1);
        }


        //double min = -(sqrt(6.0) / sqrt(size_l_minus_1 + size_l));
        //double max = (sqrt(6.0) / sqrt(size_l_minus_1 + size_l));
    }


    /**
     * @brief Returns the index of the maximum value in a single-column matrix.
     * @return Index of the maximum value
     * @note Expects a Mx1 matrix
     */
    double matrix_argmax()
    {
        try
        {
            if (cols != 1)
            {
                std::ostringstream oss;
                oss << "matrix_argmax: Dimension error: "
                    << rows << "x" << cols << std::endl
                    << "Columns must be size 1 for argmax." << endl;
                throw std::invalid_argument(oss.str());
            }
            double max_score = 0;
            int max_index = 0;
            for (int i = 0; i < rows; i++)
            {
                if (data[i][0] > max_score)
                {
                    max_score = data[i][0];
                    max_index = i;
                }
            }
            return max_index;
        }
        catch (const invalid_argument &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
        catch (const std::exception &e)
        {
            cerr << "Standard exception: " << e.what() << '\n';
        }
        catch (...)
        {
            std::cerr << "Unknown exception occurred" << std::endl;
        }
        return 0;
    }

    /**
     * @brief Flattens the matrix into a single row or column vector.
     * @param axis Axis along which to flatten (0 for column vector, 1 for row vector)
     * @return Flattened matrix
     * @note Expects a MxN matrix and returns either a (M*N)x1 or 1x(M*N) matrix
     */
    Matrix matrix_flatten(int axis) {
        // Axis = 0 -> Column Vector, Axis = 1 -> Row Vector
        Matrix result_matrix(rows, cols);
        if (axis == 0) {
            Matrix result_matrix(rows * cols, 1);
        }
        else if (axis == 1) {
            Matrix result_matrix(1, rows * cols);
        }
        else {
            printf("Argument to matrix_flatten must be 0 or 1");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (axis == 0) result_matrix.data[i * cols + j][0] = data[i][j];
                else if (axis == 1) result_matrix.data[0][i * cols + j] = data[i][j];
            }
        }
        return result_matrix;
    }

    /**
     * @brief Converts a label into a one-hot encoded column vector.
     * @param label Index of the class label
     * @note Expects a Mx1 matrix where M is the number of classes.
     */
    void matrix_column_output(int label){
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (i == label) {
                    data.at(i).at(0) = 1;
                }
                else
                {
                    data.at(i).at(0) = 0;
                }
            }
        }
    }
};

#endif // MATRIX_H