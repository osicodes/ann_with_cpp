#ifndef MSE_H
#define MSE_H

#include "loss.h"
#include "../matrix.h"

struct MSE : public Loss
{
    /// @brief True values
    Matrix y_true;

    /// @brief Predicted values
    Matrix y_pred;

    /// @brief Small constant to prevent division by zero
    const double epsilon = 1e-10; // Small constant to prevent division by zero

    /// @brief Error value
    double error = 0;

    /// @brief Mean Squared Error function
    double mse(const Matrix &matrix1, const Matrix &matrix2);

    /// @brief Derivative of Mean Squared Error function
    Matrix mse_derivative(const Matrix &matrix1, const Matrix &matrix2);

    /**
     * @brief Constructor to initialize Mean Square Error with true and predicted values
     * @param true_values Matrix of true values
     * @param predicted_values Matrix of predicted values
     */
    MSE();
    
    /**
     * @brief Performs the forward pass to compute the loss
     * @param true_values Matrix of true values
     * @param predicted_values Matrix of predicted values
     * @return Computed loss value
     */
    void forward(const Matrix &true_values, const Matrix &predicted_values);

    /**
     * @brief Performs the backward pass to compute the gradient of the loss
     * @return Matrix representing the gradient of the loss
     */
    Matrix backward();

    void update() override
    {
        // Implement any necessary updates (if applicable)
    }
};

#endif