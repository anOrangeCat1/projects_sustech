import numpy as np
import matplotlib.pyplot as plt
from utils import load_data, plot_data, plot_decision_boundary, map_feature
import copy
import math
import Logistic_Regression


def view_data(X_train, y_train):
    # Check the dimension
    print('The shape of X_train is: ' + str(X_train.shape))
    print('The shape of y_train is: ' + str(y_train.shape))
    print('We have m = %d training examples' % (len(y_train)))

    # Plot examples
    plot_data(X_train, y_train[:],
              pos_label="Admitted", neg_label="Not admitted")

    # Set the y-axis label
    plt.ylabel('Microchip Test 2')
    # Set the x-axis label
    plt.xlabel('Microchip Test 1')
    plt.legend(loc="upper right")
    plt.show()


def sigmoid(z):
    """
    Compute the sigmoid of z

    Args:
        z (ndarray): A scalar, numpy array of any size.

    Returns:
        g (ndarray): sigmoid(z), with the same shape as z

    """

    ### START CODE HERE ###
    g = 1/(1 + np.exp(-z))
    ### END SOLUTION ###

    return g


def compute_cost_reg(X, y, w, b, lambda_=1):
    """
    Computes the cost over all examples
    Args:
      X : (array_like Shape (m,n)) data, m examples by n features
      y : (array_like Shape (m,)) target value 
      w : (array_like Shape (n,)) Values of parameters of the model      
      b : (array_like Shape (n,)) Values of bias parameter of the model
      lambda_ : (scalar, float)    Controls amount of regularization
    Returns:
      total_cost: (scalar)         cost 
    """

    m, n = X.shape

    # Calls the compute_cost function that you implemented above
    cost_without_reg = Logistic_Regression.compute_cost(X, y, w, b)

    # You need to calculate this value
    reg_cost = 0.

    ### START CODE HERE ###
    for j in range(n):
        reg_cost_j = w[j]**2
        reg_cost = reg_cost + reg_cost_j
    ### END CODE HERE ###

    # Add the regularization cost to get the total cost
    total_cost = cost_without_reg + (lambda_/(2 * m)) * reg_cost

    return total_cost


def compute_gradient_reg(X, y, w, b, lambda_=1):
    """
    Computes the gradient for linear regression 

    Args:
      X : (ndarray Shape (m,n))   variable such as house size 
      y : (ndarray Shape (m,))    actual value 
      w : (ndarray Shape (n,))    values of parameters of the model      
      b : (scalar)                value of parameter of the model  
      lambda_ : (scalar,float)    regularization constant
    Returns
      dj_db: (scalar)             The gradient of the cost w.r.t. the parameter b. 
      dj_dw: (ndarray Shape (n,)) The gradient of the cost w.r.t. the parameters w. 

    """
    m, n = X.shape

    dj_db, dj_dw = Logistic_Regression.compute_gradient(X, y, w, b)

    ### START CODE HERE ###
    # Loop over the elements of w
    for j in range(n):
        dj_dw_j_reg = (lambda_ / m) * w[j]

        # Add the regularization term  to the correspoding element of dj_dw
        dj_dw[j] = dj_dw[j] + dj_dw_j_reg

    ### END CODE HERE ###

    return dj_db, dj_dw


if __name__ == "__main__":
    # with regulation
    # load dataset
    X_train, y_train = load_data("data/ex2data2.txt")
    # View the data
    # view_data(X_train, y_train)

    # Feature mapping
    print("Original shape of data:", X_train.shape)
    mapped_X = map_feature(X_train[:, 0], X_train[:, 1])
    print("Shape after feature mapping:", mapped_X.shape)
    print("X_train[0]:", X_train[0])
    print("mapped X_train[0]:", mapped_X[0])

    X_mapped = map_feature(X_train[:, 0], X_train[:, 1])

    # test compute_cost_reg()
    # X_mapped = map_feature(X_train[:, 0], X_train[:, 1])
    # np.random.seed(1)
    # initial_w = np.random.rand(X_mapped.shape[1]) - 0.5
    # initial_b = 0.5
    # lambda_ = 0.5
    # cost = compute_cost_reg(X_mapped, y_train, initial_w, initial_b, lambda_)
    # print("Regularized cost :", cost)

    # test compute_gredient_reg()
    # X_mapped = map_feature(X_train[:, 0], X_train[:, 1])
    # np.random.seed(1)
    # initial_w  = np.random.rand(X_mapped.shape[1]) - 0.5
    # initial_b = 0.5

    # lambda_ = 0.5
    # dj_db, dj_dw = compute_gradient_reg(X_mapped, y_train, initial_w, initial_b, lambda_)

    # print(f"dj_db: {dj_db}", )
    # print(f"First few elements of regularized dj_dw:\n {dj_dw[:4].tolist()}", )

    # Initialize fitting parameters
    np.random.seed(1)
    initial_w = np.random.rand(X_mapped.shape[1])-0.5
    initial_b = 1.

    # Set regularization parameter lambda_ to 1 (you can try varying this)
    lambda_ = 0.01
    # Some gradient descent settings
    iterations = 10000
    alpha = 0.01

    w, b, J_history, _ = Logistic_Regression.gradient_descent(X_mapped, y_train, initial_w, initial_b,
                                                              compute_cost_reg, compute_gradient_reg,
                                                              alpha, iterations, lambda_)
    plot_decision_boundary(w, b, X_mapped, y_train)

    # Compute accuracy on the training set
    p = Logistic_Regression.predict(X_mapped, w, b)

    print('Train Accuracy: %f' % (np.mean(p == y_train) * 100))
