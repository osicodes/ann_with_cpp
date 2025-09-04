
#include <sstream>
// #include "Matrix.h" // Add this line if Matrix is defined in Matrix.h
#include "matrixUtils.h"
using namespace std;

// Add utility functions for matrix operations here if needed in the future
namespace MatrixUtils
{
    
    /**
     * @brief Returns true if dimensions match for element-wise operations
     * @param matrix1 First matrix
     * @param matrix2 Second matrix
     * @param error_condition Optional error message prefix
     * @return True if dimensions match, otherwise throws an exception
     * @throws invalid_argument: Dimension mistmatch multiply
     */
    void check_same_dimensions(const Matrix &matrix1, const Matrix &matrix2, const string &error_condition)
    {
        if (matrix1.rows == matrix2.rows && matrix1.cols == matrix2.cols)
            return;
        ostringstream msg;
        msg << error_condition
            << matrix1.rows << "x" << matrix1.cols << " "
            << matrix2.rows << "x" << matrix2.cols << endl
            << "Matrices must have the same dimensions." << endl;
        throw runtime_error(msg.str());
    }

    /**
     * @brief Checks if two matrices are compatible for dot product
     * @param matrix1 First matrix
     * @param matrix2 Second matrix
     * @param context Optional context message for error reporting
     */
    void check_dot_product_compatible(const Matrix &matrix1, const Matrix &matrix2, const string &context)
    {
        if (matrix1.cols != matrix2.rows)
        {
            ostringstream msg;
            msg << context
                << matrix1.rows << "x" << matrix1.cols << " "
                << matrix2.rows << "x" << matrix2.cols << endl
                << "Matrix A columns must match Matrix B rows.";
            throw runtime_error(msg.str());
        }
    }

    /**
     * @brief Checks if a matrix is square
     * @param matrix Input matrix
     * @param context Optional context message for error reporting
     */
    void check_square_matrix(const Matrix &matrix, const string &context)
    {
        if (matrix.rows != matrix.cols)
        {
            ostringstream msg;
            msg << context
                << matrix.rows << "x" << matrix.cols << endl
                << "Matrix must be square.";
            throw runtime_error(msg.str());
        }
    }

    
    /**
     * @brief Checks if a matrix is a column matrix (cols == 1)
     * @param matrix Input matrix
     * @param context Optional context message for error reporting
     * @throws runtime_error if the matrix is not a column matrix
     */
    void check_column_matrix(const Matrix &matrix, const string &context)
    {
        if (matrix.cols != 1)
        {
            ostringstream msg;
            msg << context
                << matrix.rows << "x" << matrix.cols << endl
                << "Matrix must be a column matrix (cols == 1).";
            throw runtime_error(msg.str());
        }
    }

    /**
     * @brief Applies a given function to each element of the matrix
     * @param func Function pointer to the function to be applied
     * @param matrix Input matrix
     * @return New matrix with the function applied to each element
     */
    Matrix apply_function(double (*func)(double), const Matrix &matrix)
    {
        Matrix result_matrix = matrix.matrix_copy();
        for (int i = 0; i < matrix.rows; i++)
        {
            for (int j = 0; j < matrix.cols; j++)
            {
                result_matrix.data[i][j] = (*func)(matrix.data[i][j]);
            }
        }
        return result_matrix;
    }
}