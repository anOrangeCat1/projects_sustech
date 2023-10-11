"""
Introduction
KNN_od.py means:
In this python file, the Logistic Regression method and original 
dataset(origin_breast_cancer_data.csv) are used.

Dataset: origin_breast_cancer_data.csv
    357 benign and 212 malignant samples.
    357+212=569 samples in total
    Therefore, in this case, Training_set : Test_set = 4 : 1
    Training_set = 455
    Test_set = 114

Algorithm: Logistic Regression

Functions:
    data_set1           use all data (30 columns) to train the model,
                        observe the results and try to optimize

                        ->return x_train, x_test, y_train, y_test
    =============================================================                
    LR_l1               use Logistic Regression with l1 regulation to 
                        train model and predict, find the small parameters,
                        not use them next time
                    
                        ->return col_opt
    =============================================================                
    data_set_opt        after the LR_l1, select the optimized data 
                        to train
    
                        ->return x_train_opt
    =============================================================
    LR_l2               use Logistic Regression with l2 regualtion to
                        train model and predict
    =============================================================
    data_stander        use functions in sklearn to make data standeration

                        ->return x_train_ss, x_test_ss
    =============================================================
    data_normaliztion   use functions in sklearn to make data
                        normaliaziton
                        
                        ->return x_trian_mm, x_test_mm

    """

import numpy as np
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import recall_score, precision_score, f1_score
from sklearn.preprocessing import MinMaxScaler, StandardScaler
import random


def data_set1(data_set_path):
    """Use all data (30 columns) to train the model"""

    random.seed(2022)
    all_cols = range(2, 32, 1)
    all_rows = range(0, 569)
    test_num = random.sample(all_rows, 114)
    train_num = [i for i in all_rows if i not in test_num]
    # print(len(test_num))
    # print(len(train_num))
    # print(len(all_rows))
    # print(test_num)
    # for i in test_num:
    #     for j in train_num:
    #         if i == j:
    #             print("no!")

    x_all = np.loadtxt(data_set_path, delimiter=',',
                       skiprows=1, usecols=all_cols)
    # print(len(X_all))
    x_train = x_all[train_num, :]
    x_test = x_all[test_num, :]
    # print(len(x_train))
    # print(len(x_test))

    y_all_str = np.loadtxt(data_set_path, dtype=str,
                           delimiter=',', skiprows=1, usecols=(1))
    y_all = np.zeros(len(y_all_str))
    for i, diagnosis in np.ndenumerate(y_all_str):
        if diagnosis == 'M':
            y_all[i] = 1
        else:
            y_all[i] = 0
    y_train = y_all[train_num]
    y_test = y_all[test_num]

    return x_train, x_test, y_train, y_test


def LR_l1(x_train, x_test, y_train, y_test):
    """use l1 regualtion"""

    lr_model_l1 = LogisticRegression(
        penalty="l1", solver="liblinear", max_iter=1000)
    lr_model_l1.fit(x_train, y_train)
    y_pred = lr_model_l1.predict(x_test)

    coef_l1 = lr_model_l1.coef_
    recall_l1 = recall_score(y_test, y_pred)
    precision_l1 = precision_score(y_test, y_pred)
    f1_l1 = f1_score(y_test, y_pred)

    all_cols = range(0, 30, 1)
    col_zero = []
    col_opt = []

    for i, a in np.ndenumerate(coef_l1):
        if a == 0.0:
            col_zero.append(i[1])

    col_opt = [i for i in all_cols if i not in col_zero]

    # print(all_cols)
    # print(col_zero)
    # print(col_opt)
    print("weights = ")
    print(lr_model_l1.coef_)
    print("recall = ", recall_l1)
    print("precision = ", precision_l1)
    print("f1_score = ", f1_l1)

    return col_opt


def LR_l2(x_train, x_test, y_train, y_test):
    lr_model_l2 = LogisticRegression(
        penalty="l2", solver="liblinear", max_iter=1000)
    lr_model_l2.fit(x_train, y_train)
    y_pred = lr_model_l2.predict(x_test)
    recall_l2 = recall_score(y_test, y_pred)
    precision_l2 = precision_score(y_test, y_pred)
    f1_l2 = f1_score(y_test, y_pred)

    print("weights = ")
    print(lr_model_l2.coef_)
    print("recall = ", recall_l2)
    print("precision = ", precision_l2)
    print("f1_score = ", f1_l2)


def data_set_opt(x_train, x_test, col_opt):
    x_train_opt = x_train[:, col_opt]
    x_test_opt = x_test[:, col_opt]

    # print(x_train_opt.shape)

    return x_train_opt, x_test_opt


def data_stander(x_train, x_test):
    """standardization scale"""
    ss = StandardScaler()
    x_train_ss = ss.fit_transform(x_train)
    x_test_ss = ss.fit_transform(x_test)

    return x_train_ss, x_test_ss


def data_normalization(x_train, x_test):
    """normalization scale"""
    mm = MinMaxScaler()
    x_train_mm = mm.fit_transform(x_train)
    x_test_mm = mm.fit_transform(x_test)

    return x_train_mm, x_test_mm


if __name__ == "__main__":
    data_set_path = './data/origin_breast_cancer_data.csv'
    x_train, x_test, y_train, y_test = data_set1(data_set_path)

    # use logistic regression with l1 regulation
    print("="*80)
    print("Logistic Regression with l1 Regulation")
    print()
    # find the too small weights, meaning little influence to the model
    col_opt = LR_l1(x_train, x_test, y_train, y_test)

    # use logistic regression with l1 regulation
    print("="*80)
    print("Logistic Regression with l2 Regulation")
    print()
    LR_l2(x_train, x_test, y_train, y_test)

    # after stander scale
    print("="*80)
    print("after stander scale of data")
    print("Logistic Regression with l2 Regulation by selecting data")
    print()
    x_train_ss, x_test_ss = data_stander(x_train, x_test)
    LR_l2(x_train_ss, x_test_ss, y_train, y_test)

    # after normaliztion scale
    print("="*80)
    print("after normalize scale of data")
    print("Logistic Regression with l2 Regulation by selecting data")
    print()
    x_train_mm, x_test_mm = data_normalization(x_train, x_test)
    LR_l2(x_train_mm, x_test_mm, y_train, y_test)

    # select the optimized datas
    x_train_opt, x_test_opt = data_set_opt(x_train, x_test, col_opt)
    print("-"*80)
    print("after selecting the optimized datas")
    print("-"*80)

    # use logistic regression with l2 regulation
    print("="*80)
    print("Logistic Regression with l2 Regulation by selecting data")
    print()
    LR_l2(x_train_opt, x_test_opt, y_train, y_test)

    # after stander scale
    print("="*80)
    print("after stander scale of data")
    print("Logistic Regression with l2 Regulation by selecting data")
    print()
    x_train_opt_ss, x_test_opt_ss = data_stander(x_train_opt, x_test_opt)
    LR_l2(x_train_opt_ss, x_test_opt_ss, y_train, y_test)

    # after normaliztion scale
    print("="*80)
    print("after normalize scale of data")
    print("Logistic Regression with l2 Regulation by selecting data")
    print()
    x_train_opt_mm, x_test_opt_mm = data_normalization(x_train_opt, x_test_opt)
    LR_l2(x_train_opt_mm, x_test_opt_mm, y_train, y_test)
