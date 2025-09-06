#pragma once
#include "../matrix.h"
#include "../constants.h"

struct Optimizer
{
    double learning_rate;
    Optimizer(double lr = DEFAULT_LEARNING_RATE) : learning_rate(lr) {};
protected:
    virtual void update(Matrix &weights, const Matrix &weights_gradient, const double learning_rate) {};
};