
#include "matrix.h"

double Matrix::uniform_distribution(double low, double high)
{

    static double difference = high - low; // The difference between the two
    static int scale = 10000;              // Scaling factor to convert to integer range
    static int scaled_difference = (int)(difference * scale);
    return low + (1.0 * (rand() % scaled_difference) / scale);
}

Matrix::Matrix(int row, int col) : rows(row), cols(col), data(row, vector<double>(col, 0.0))
{
}

double &Matrix::define_value_at(int i, int j)
{
    return data.at(i).at(j);
}

void Matrix::matrix_print()
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

void Matrix::matrix_fill_with_same_value(double number)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data.at(i).at(j) = number;
        }
    }
}

void Matrix::matrix_fill_with_value_from_user()
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

Matrix Matrix::matrix_copy() const
{
    return *this;
}

void Matrix::matrix_save(const string &filename)
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

void Matrix::matrix_randomize(int n)
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

void Matrix::matrix_custom_randomize(int input, int current, const string &initializationfunc)
{
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
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                data[i][j] = uniform_distribution(min, max);
            }
        }
    }
    else if (initializationfunc == "glorot_norm")
    {
        double min = -sqrt(2) / sqrt(size_l_minus_1 + size_l);
        double max = sqrt(2) / sqrt(size_l_minus_1 + size_l);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                data[i][j] = uniform_distribution(min, max);
            }
        }
    }
    else
    {
        cout << initializationfunc << " is not a supported initialization method" << endl;
        exit(1);
    }

    // double min = -(sqrt(6.0) / sqrt(size_l_minus_1 + size_l));
    // double max = (sqrt(6.0) / sqrt(size_l_minus_1 + size_l));
}

Matrix Matrix::matrix_flatten(int axis)
{
    // Axis = 0 -> Column Vector, Axis = 1 -> Row Vector
    Matrix result_matrix(rows, cols);
    if (axis == 0)
    {
        Matrix result_matrix(rows * cols, 1);
    }
    else if (axis == 1)
    {
        Matrix result_matrix(1, rows * cols);
    }
    else
    {
        printf("Argument to matrix_flatten must be 0 or 1");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (axis == 0)
                result_matrix.data[i * cols + j][0] = data[i][j];
            else if (axis == 1)
                result_matrix.data[0][i * cols + j] = data[i][j];
        }
    }
    return result_matrix;
}

void Matrix::matrix_column_output(int label)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == label)
            {
                data.at(i).at(0) = 1;
            }
            else
            {
                data.at(i).at(0) = 0;
            }
        }
    }
}