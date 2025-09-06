#ifndef LOSS_H
#define LOSS_H

#include "../matrix.h"

struct Loss
{
    virtual void forward(const Matrix &true_values, const Matrix &predicted_values) {};
    virtual Matrix backward() {
        return Matrix();
    };
    virtual void update() {};
};

#endif