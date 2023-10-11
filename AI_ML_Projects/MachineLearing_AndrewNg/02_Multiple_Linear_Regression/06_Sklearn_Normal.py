import matplotlib.pyplot as plt
from lab_utils_multi import load_house_data
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LinearRegression, SGDRegressor
import numpy as np
np.set_printoptions(precision=2)
dlblue = '#0096ff'
dlorange = '#FF9300'
dldarkred = '#C00000'
dlmagenta = '#FF40FF'
dlpurple = '#7030A0'
plt.style.use('./deeplearning.mplstyle')

if __name__ == "__main__":
    # Load the data set
    X_train = np.array([1.0, 2.0])  # features
    y_train = np.array([300, 500])  # target value
    # print(X_train.shape)
    # print(X_train.reshape(-1,1).shape)

    # Create and fit the model
    linear_model = LinearRegression()
    # X must be a 2-D Matrix
    linear_model.fit(X_train.reshape(-1, 1), y_train)

    # View Parameters
    b = linear_model.intercept_
    w = linear_model.coef_
    print(f"w = {w:}, b = {b:0.2f}")
    print(f"'manual' prediction: f_wb = wx+b : {1200*w + b}")

    # Make Predictions
    y_pred = linear_model.predict(X_train.reshape(-1, 1))
    print("Prediction on trainning set:", y_pred)

    X_test = np.array([[1200]])
    print(
        f"Prediction for 1200 sqft house: ${linear_model.predict(X_test)[0]:0.2f}")

    # load the dataset
    X_train, y_train = load_house_data()
    X_features = ['size(sqft)', 'bedrooms', 'floors', 'age']

    linear_model = LinearRegression()
    linear_model.fit(X_train, y_train)

    b = linear_model.intercept_
    w = linear_model.coef_
    print(f"w = {w:}, b = {b:0.2f}")

    print(f"Prediction on training set:\n {linear_model.predict(X_train)[:4]}")
    print(f"prediction using w,b:\n {(X_train @ w + b)[:4]}")
    print(f"Target values \n {y_train[:4]}")

    x_house = np.array([1200, 3, 1, 40]).reshape(-1, 4)
    x_house_predict = linear_model.predict(x_house)[0]
    print(
        f" predicted price of a house with 1200 sqft, 3 bedrooms, 1 floor, 40 years old = ${x_house_predict*1000:0.2f}")
