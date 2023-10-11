"""
---Regression---

Goal: Predict something
continuous outputs (like scores) -- t
Predicting continuous outputs is called regression

How to predict?:
    Features: called x
    Training examples: many x(i) and t(i) are known
    A Model: a function that the relationship between x and t
    A Loss or Cost or an Objective function: how well
    Optimization: find the parameters to minimize the loss function

a simple model: linear equation -- y(x) = w0 + w1x
what mode we choose is very important

A simple model typically does not exactly fit the data: the noise 
Sources of noise:
    Imprecision in data attributes (input noise)
    Error in data targets (mis-labeling)
    Additional attributes
    Model (maybe too simple)


the below example shows a toy example of linear regression

"""

from re import I
import torch
import torch.nn as nn
import numpy as np
import matplotlib.pyplot as plt


if __name__ == "__main__":
    # Hyper-parameters
    input_size = 1
    output_size = 1
    num_epochs = 60
    learning_rate = 0.001

    i_iter = np.array([])
    loss_iter = np.array([])

    # Toy dataset
    x_train = np.array([[3.3], [4.4], [5.5], [6.71], [6.93], [4.168], [9.779], [
                       6.182], [7.59], [2.167], [7.042], [10.791], [5.313], [7.997], [3.1]], dtype=np.float32)
    y_train = np.array([[1.7], [2.76], [2.09], [3.19], [1.694], [1.573], [3.366], [2.596], [
                       2.53], [1.221], [2.827], [3.465], [1.65], [2.904], [1.3]], dtype=np.float32)

    # Linear regression model
    model = nn.Linear(input_size, output_size)

    # Loss and Optimizer
    criterion = nn.MSELoss()
    optimizer = torch.optim.SGD(model.parameters(), lr=learning_rate)

    # Train the model
    for epoch in range(num_epochs):
        # Convert numpy arrays to torch tensors
        inputs = torch.from_numpy(x_train)
        targets = torch.from_numpy(y_train)

        # Forward pass
        outputs = model(inputs)
        loss = criterion(outputs,targets)

        # Backward and optimize
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        i_iter = np.append(i_iter,epoch)
        loss_iter = np.append(loss_iter,loss.item())
        
        if(epoch+1)%5 == 0:
            print('Epoch [{}/{}], Loss: {:.4f}'.format(epoch+1,num_epochs,loss.item()))

        # Plot the graph
        predicted = model(torch.from_numpy(x_train)).detach().numpy()

    plt.figure()
    plt.plot(x_train,y_train,'ro',label='Original data')
    plt.plot(x_train,predicted,label='Fitted line')
    plt.legend()

    plt.figure()
    plt.plot(i_iter,loss_iter)
    plt.show()
