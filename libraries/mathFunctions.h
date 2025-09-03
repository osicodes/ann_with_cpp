#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include "matrix.h"

Matrix multiply(Matrix matrix1, Matrix matrix2);
Matrix add(Matrix matrix1, Matrix matrix2);
Matrix subtract(Matrix matrix1, Matrix matrix2);
Matrix beforeSoftmax(Matrix matrix);
Matrix dot_product(Matrix matrix1, Matrix matrix2);
Matrix identity_matrix(const int &num);
Matrix scale(const double &scale_value, const Matrix &matrix);
Matrix addScalar(const double &scale_value, const Matrix &matrix);
Matrix transpose(const Matrix &matrix);
double determinant(const Matrix &matrix);
double mse(const Matrix &matrix1, const Matrix &matrix2);
Matrix mse_derivative(const Matrix &matrix1, const Matrix &matrix2);
double cross_enthropy(const Matrix m1, const Matrix m2);
Matrix cross_enthropy_derivative(const Matrix &m1, const Matrix &m2);

#endif // MATHFUNCTIONS_H