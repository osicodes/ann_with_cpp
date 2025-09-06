#include "mse.h"
#include "../functions/mathFunctions.h"

#include "../matrixUtils.h"
using namespace std;
using namespace MatrixUtils;

MSE::MSE() {}

/**
 * @brief Calculates the Mean Squared Error (MSE) between two matrices
 * @param matrix1 First matrix (true values)
 * @param matrix2 Second matrix (predicted values)
 * @return Mean Squared Error value
 */
double MSE::mse(const Matrix &matrix1, const Matrix &matrix2)
{
    check_same_dimensions(matrix1, matrix2, "Dimension mistmatch mean square error: ");
    // true_y - predicted_y
    double error = 0.0;
    for (int i = 0; i < matrix1.rows; i++)
    {
        for (int j = 0; j < matrix2.cols; j++)
        {
            error += pow(matrix1.data[i][j] - matrix2.data[i][j], 2);
        }
    }
    return error / matrix1.rows;
}

/**
 * @brief Calculates the derivative of the Mean Squared Error (MSE) with respect to the predicted values
 * @param matrix1 First matrix (true values)
 * @param matrix2 Second matrix (predicted values)
 * @return Matrix representing the derivative of MSE
 */
Matrix MSE::mse_derivative(const Matrix &matrix1, const Matrix &matrix2)
{
    // Mean Square error prime  ---  d(cost func)/d(activated output)
    Matrix output = subtract(matrix1, matrix2); // true_y - predicted_y
    const double sc = 2.0 / matrix1.rows;
    return scale(sc, output);
}

void MSE::forward(const Matrix &true_values, const Matrix &predicted_values)
{
    y_true = true_values;
    y_pred = predicted_values;
    error = mse(y_true, y_pred);
}

Matrix MSE::backward()
{
    return mse_derivative(y_true, y_pred);
}