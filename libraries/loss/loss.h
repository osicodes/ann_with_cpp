#ifndef LOSS_H
#define LOSS_H

#include "../matrix.h"

struct Loss
{

    /// @brief Error value
    double error = 0;

    virtual void forward(const Matrix &true_values, const Matrix &predicted_values) = 0;
    virtual Matrix backward()
    {
        return Matrix();
    };
    virtual void update() {};
};

#endif