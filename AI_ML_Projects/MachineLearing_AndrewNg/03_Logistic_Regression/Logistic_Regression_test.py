import numpy as np
import matplotlib.pyplot as plt
import utils
import copy
import math
import solutions


def gradient_descent(X, y, w_in, b_in, cost_function, gradient_function, alpha, num_iters, lambda_):
    """
    Performs batch gradient descent to learn theta. Updates theta by taking 
    num_iters gradient steps with learning rate alpha

    Args:
      X :    (array_like Shape (m, n)
      y :    (array_like Shape (m,))
      w_in : (array_like Shape (n,))  Initial values of parameters of the model
      b_in : (scalar)                 Initial value of parameter of the model
      cost_function:                  function to compute cost
      alpha : (float)                 Learning rate
      num_iters : (int)               number of iterations to run gradient descent
      lambda_ (scalar, float)         regularization constant

    Returns:
      w : (array_like Shape (n,)) Updated values of parameters of the model after
          running gradient descent
      b : (scalar)                Updated value of parameter of the model after
          running gradient descent
    """

    # number of training examples
    m = len(X)

    # An array to store cost J and w's at each iteration primarily for graphing later
    J_history = []
    w_history = []

    for i in range(num_iters):

        # Calculate the gradient and update the parameters
        dj_db, dj_dw = gradient_function(X, y, w_in, b_in, lambda_)

        # Update Parameters using w, b, alpha and gradient
        w_in = w_in - alpha * dj_dw
        b_in = b_in - alpha * dj_db

        # Save cost J at each iteration
        if i < 100000:      # prevent resource exhaustion
            cost = cost_function(X, y, w_in, b_in, lambda_)
            J_history.append(cost)

        # Print cost every at intervals 10 times or as many iterations if < 10
        if i % math.ceil(num_iters/10) == 0 or i == (num_iters-1):
            w_history.append(w_in)
            print(f"Iteration {i:4}: Cost {float(J_history[-1]):8.2f}   ")

    # return w and J,w history for graphing
    return w_in, b_in, J_history, w_history


def ex1():
    print("sigmoid(0) = " + str(solutions.sigmoid(0)))


def ex2(X_train, y_train):
    m, n = X_train.shape

    # Compute and display cost with w initialized to zeroes
    initial_w = np.zeros(n)
    initial_b = 0.
    cost = solutions.compute_cost(X_train, y_train, initial_w, initial_b)
    print('Cost at initial w (zeros): {:.3f}'.format(cost))

    # Compute and display cost with non-zero w
    test_w = np.array([0.2, 0.2])
    test_b = -24.
    cost = solutions.compute_cost(X_train, y_train, test_w, test_b)
    print('Cost at test w,b: {:.3f}'.format(cost))

    return initial_w, initial_b


def ex3(X_train, y_train):
    m, n = X_train.shape

    # Compute and display gradient with w initialized to zeroes
    initial_w = np.zeros(n)
    initial_b = 0.

    dj_db, dj_dw = solutions.compute_gradient(
        X_train, y_train, initial_w, initial_b)
    print(f'dj_db at initial w (zeros):{dj_db}')
    print(f'dj_dw at initial w (zeros):{dj_dw.tolist()}')

    # Compute and display cost and gradient with non-zero w
    test_w = np.array([0.2, -0.5])
    test_b = -24
    dj_db, dj_dw = solutions.compute_gradient(X_train, y_train, test_w, test_b)

    print('dj_db at test_w:', dj_db)
    print('dj_dw at test_w:', dj_dw.tolist())


def ex4(X_train, y_train, compute_cost, compute_gradient):
    np.random.seed(1)
    initial_w = 0.01 * (np.random.rand(2).reshape(-1, 1) - 0.5)
    initial_b = -8

    # Some gradient descent settings
    iterations = 10000
    alpha = 0.001

    w, b, J_history, _ = gradient_descent(X_train, y_train, initial_w, initial_b,
                                          compute_cost, compute_gradient, alpha, iterations, 0)
    # print("-----ex4-----")
    # print("w: ", w)
    # print("b: ", b)
    # print("J_history: ", J_history)


if __name__ == "__main__":
    # Loading and visualizing the data
    X_train, y_train = utils.load_data("./data/ex2data1.txt")
    # View the variable
    # X_train contains exam scores on two exams for a student
    # y_train is the admission decision
    #   y_train = 1 if the student was admitted
    #   y_train = 0 if the student was not admitted
    # Both X_train and y_train are numpy arrays.
    print("First five elements in X_train are:\n", X_train[:5])
    print("Type of X_train:", type(X_train))
    print("First five elements in y_train are:\n", y_train[:5])
    print("Type of y_train:", type(y_train))
    # Check the dimensions of variables
    print('The shape of X_train is: ' + str(X_train.shape))
    print('The shape of y_train is: ' + str(y_train.shape))
    print('We have m = %d training examples' % (len(y_train)))

    # Plot examples
    utils.plot_data(
        X_train, y_train[:], pos_label="Admitted", neg_label="Not admitted")
    # Set the y-axis label
    plt.ylabel('Exam 2 score')
    # Set the x-axis label
    plt.xlabel('Exam 1 score')
    plt.legend(loc="upper right")
    plt.show()
    
    # initialize w and b
    m, n = X_train.shape
    initial_w = np.zeros(n)
    initial_b = 0.

    # ex1()

    # ex3(X_train, y_train)

    ex4(X_train, y_train, 
        solutions.compute_cost, solutions.compute_gradient)
