#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include "../matrix.h"

Matrix multiply(const Matrix &matrix1, const Matrix &matrix2);
Matrix add(const Matrix &matrix1, const Matrix &matrix2);
Matrix subtract(const Matrix &matrix1, const Matrix &matrix2);
Matrix beforeSoftmax(const Matrix &matrix);
Matrix dot_product(const Matrix &matrix1, const Matrix &matrix2);
Matrix identity_matrix(const int &num);
Matrix scale(const double &scale_value, const Matrix &matrix);
Matrix addScalar(const double &scale_value, const Matrix &matrix);
Matrix transpose(const Matrix &matrix);
double determinant(const Matrix &matrix);
double matrix_argmax(const Matrix &matrix);
double cross_enthropy(const Matrix m1, const Matrix m2);
Matrix cross_enthropy_derivative(const Matrix &m1, const Matrix &m2);

#endif // MATHFUNCTIONS_H