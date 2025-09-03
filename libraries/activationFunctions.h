#ifndef ACTIVATIONFUNCTIONS_H
#define ACTIVATIONFUNCTIONS_H

#include "matrix.h"

double sigmoid(const double input);
double sigmoid_prime(const double input);
double relu(const double input);
double relu_prime(const double input);
double tan_h(const double input);
double tan_h_prime(const double input);
Matrix sigmoidPrime(Matrix matrix);
Matrix softmax(Matrix matrix);
Matrix softmax_prime(int sz, Matrix matrix);

#endif