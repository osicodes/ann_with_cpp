#ifndef LAYER_H
#define LAYER_H
#include "../matrix.h"

struct Layer
{
    virtual Matrix forward_propagation(const Matrix &input) = 0;
    virtual Matrix backward_propagation(const Matrix &output_gradient, const double learning_rate) = 0;

protected:
    virtual void update(const Matrix &weights_gradient, const Matrix &output_gradient, const double learning_rate) = 0;
};

#endif