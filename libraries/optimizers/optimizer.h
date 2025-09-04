#pragma once
#include "matrix.h"

struct Optimizer
{
    virtual void update(Matrix &weights, const Matrix &weights_gradient, const double learning_rate) = 0;
    double learning_rate;
};