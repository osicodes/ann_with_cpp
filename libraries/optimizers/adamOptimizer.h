#ifndef ADAM_H
#define ADAM_H
#include "optimizer.h"
#include "../constants.h"

struct ADAM : Optimizer
{
    ADAM(double lr = DEFAULT_LEARNING_RATE);

protected:
    void update(Matrix &, const Matrix &, const double ) override
    {
    }
};

#endif