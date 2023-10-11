"""
Introduction

KNN_ud.py means:
In this python file, the KNN method and unbalanced dataset
(breast_cancer_data_357B_100M.csv) are used.

Dataset:breast_cancer_data_357B_100M.csv
    contains 357 benign and 100 malignant samples.
    357+100=457 samples in total

Algorithm: KNN

Functions:
    data_set1           use all data (30 columns) to train the model,
                        observe the results and try to optimize

                        ->return x_train, x_test, y_train, y_test
    =============================================================
    find_best_k         tranverse k to find the highest score and 
                        its relative k (hyper-parameters)
    =============================================================
    KNN                 use the KNN model to predict
    =============================================================
    data_stander        use functions in sklearn to make data standeration

                        ->return x_train_ss, x_test_ss
    =============================================================
    data_normaliztion   use functions in sklearn to make data
                        normaliaziton
                        
                        ->return x_trian_mm, x_test_mm
    """

import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import recall_score, precision_score, f1_score
from sklearn.preprocessing import MinMaxScaler, StandardScaler
import random
import matplotlib.pyplot as plt


def data_set1(data_set_path):
    """Use all data (30 columns) to train the model"""

    random.seed(2022)
    all_cols = range(2, 32, 1)
    all_rows = range(0, 457)
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


# def data_set2(data_set_path):
#     """select 30m and 84b to train"""
#     all_cols = range(2, 32, 1)
#     all_rows = range(0, 457)
#     x_all = np.loadtxt(data_set_path, delimiter=',',
#                        skiprows=1, usecols=all_cols)
#     y_all_str = np.loadtxt(data_set_path, dtype=str,
#                            delimiter=',', skiprows=1, usecols=(1))
#     y_all = np.zeros(len(y_all_str))
#     for i, diagnosis in np.ndenumerate(y_all_str):
#         if diagnosis == 'M':
#             y_all[i] = 1
#         else:
#             y_all[i] = 0

#     # print(y_all)
#     test_num_m = np.zeros(30)
#     test_num_b = np.zeros(84)
#     counter_m = 0
#     counter_b = 0
    
#     for i, a in enumerate(y_all):
#         if counter_m >= 30:
#             break
#         if a == 0:
#             test_num_m[counter_m]=i
#             counter_m += 1
            

#     for i, a in enumerate(y_all):
#         if counter_b >= 84:
#             break
#         if a == 1:
#             test_num_m[counter_b]=i
#             counter_b += 1
            
#     test_num = test_num_b.append(test_num_m)
#     print(len(test_num))
#     print(test_num)

def find_best_k(x_train, x_test, y_train, y_test):
    """find the best k when getting the highest score"""
    ks = np.arange(1, 100, 1)
    scores = []
    for k in ks:
        knn = KNeighborsClassifier(n_neighbors=k)
        knn.fit(x_train, y_train)
        score = knn.score(x_test, y_test)
        scores.append(score)
    scores = np.array(scores)
    # print("the highest score = ", max(scores))

    best_k = 0
    for i, a in enumerate(scores):
        # print(a)
        if a == max(scores):
            best_k = i+1
    # print(best_k)

    plt.plot(ks, scores)
    plt.xlabel('k')
    plt.ylabel('score')
    plt.show()

    return best_k


def KNN(x_train, x_test, y_train, y_test, best_k):
    knn = KNeighborsClassifier(n_neighbors=best_k)
    knn.fit(x_train, y_train)
    y_pred = knn.predict(x_test)
    recall = recall_score(y_pred, y_test)
    precision = precision_score(y_pred, y_test)
    f1 = f1_score(y_test, y_pred)

    print("k = ", best_k)
    print("recall = ", recall)
    print("precision = ", precision)
    print("f1_score = ", f1)


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

    # standardize data
    x_train_ss, x_test_ss = data_stander(x_train, x_test)
    # normalize data
    x_train_mm, x_test_mm = data_normalization(x_train, x_test)

    # find the best k in different cases
    best_k = find_best_k(x_train, x_test, y_train, y_test)
    best_k_ss = find_best_k(x_train_ss, x_test_ss, y_train, y_test)
    best_k_mm = find_best_k(x_train_mm, x_test_mm, y_train, y_test)
    # use KNN to predict
    print("="*80)
    print("KNN without pre-process of data")
    print()
    KNN(x_train, x_test, y_train, y_test, best_k)

    print("="*80)
    print("KNN with standardization of data")
    print()
    KNN(x_train_ss, x_test_ss, y_train, y_test, best_k_ss)

    print("="*80)
    print("KNN with normalization of data")
    print()
    KNN(x_train_mm, x_test_mm, y_train, y_test, best_k_mm)

    # data_set2(data_set_path)
