#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include "matrix.h" 
using namespace std;

// #include <string>

namespace MatrixUtils
{
    // Add utility functions for matrix operations here if needed in the future
    void check_same_dimensions(const Matrix &matrix1, const Matrix &matrix2, const string &error_condition = "");
    void check_dot_product_compatible(const Matrix &m1, const Matrix &m2, const string &context = "");
    void check_square_matrix(const Matrix &matrix, const string &context = "");
    void check_column_matrix(const Matrix &matrix, const string &context = "");
    Matrix apply_function(double (*func)(double), const Matrix &matrix);
}
#endif